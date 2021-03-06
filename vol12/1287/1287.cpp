#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <iostream>
#include <queue>

using namespace std;

typedef long long LL;

#define PB push_back
#define FRO freopen("in.txt","r",stdin);

#define CLR(arr) memset( (arr),0,sizeof(arr) );
#define NEG(arr) memset( (arr),-1,sizeof(arr) );

typedef pair<int,int> pint;
typedef map<int,int> mint;

typedef pair<double ,bool > pdb;

pdb dp[1<<16][16];
bool vis[1<<16][16];

int node;
vector<int> out[16];
vector<int> cost[16];

int Set(int N,int pos){
    return N=N | (1<<pos);
}
int reset(int N,int pos){
    return N= N & ~(1<<pos);
}
bool check(int N,int pos){
    return (bool)(N & (1<<pos));
}



pdb func( int state,int now ){
    //printf("%d %d\n",state,now);
    if ( state==(1<<node)-1 )return make_pair(0,true);

    else if ( vis[state][now] )return dp[state][now];

    int cnt=0;
    double sum=0;
    for (int i=0;i<out[now].size();++i){
        //printf("in %d going %d\n",now,out[now][i]);
        if ( check( state,out[now][i] )==0 && func( Set(state,out[now][i]),out[now][i] ).second==true ){
            cnt++;
            sum += cost[now][i]+func( Set(state,out[now][i]),out[now][i] ).first;
        }
    }
    if ( cnt==0 )return make_pair(0,false);
    cnt++;



    sum= ( sum/cnt+5.0/cnt )/( 1- 1.0/cnt );

    vis[state][now]=true;
    dp[state][now].first=sum;
    dp[state][now].second=true;
    return dp[state][now];
}

int main(){
    FRO

    int kase;
    scanf("%d",&kase);

    for (int kk=1;kase--;++kk){

        int ee;
        scanf("%d %d",&node,&ee);

        for (int i=0;i<node;++i){
            out[i].clear();
            cost[i].clear();
        }

        int u,v,w;
        while ( ee-- ){
            scanf("%d %d %d",&u,&v,&w);

            out[u].PB(v);
            cost[u].PB(w);

            out[v].PB(u);
            cost[v].PB(w);

        }

        CLR(vis);

        printf("Case %d: %.8lf\n",kk,func( 1,0 ).first);

    }


    return 0;
}

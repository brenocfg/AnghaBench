#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUFSIZ ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_prepbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_objlen (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_chars(lua_State*L,FILE*f,size_t n){
size_t rlen;
size_t nr;
luaL_Buffer b;
luaL_buffinit(L,&b);
rlen=BUFSIZ;
do{
char*p=luaL_prepbuffer(&b);
if(rlen>n)rlen=n;
nr=fread(p,sizeof(char),rlen,f);
luaL_addsize(&b,nr);
n-=nr;
}while(n>0&&nr==rlen);
luaL_pushresult(&b);
return(n==0||lua_objlen(L,-1)>0);
}
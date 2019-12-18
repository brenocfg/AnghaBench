#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {char const* src_init; char const* src_end; scalar_t__ level; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ MatchState ;

/* Variables and functions */
 char* lmemfind (char const*,size_t,char const*,size_t) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* match (TYPE_1__*,char const*,char const*) ; 
 int posrelat (int /*<<< orphan*/ ,size_t) ; 
 int push_captures (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/ * strpbrk (char const*,char*) ; 

__attribute__((used)) static int str_find_aux(lua_State*L,int find){
size_t l1,l2;
const char*s=luaL_checklstring(L,1,&l1);
const char*p=luaL_checklstring(L,2,&l2);
ptrdiff_t init=posrelat(luaL_optinteger(L,3,1),l1)-1;
if(init<0)init=0;
else if((size_t)(init)>l1)init=(ptrdiff_t)l1;
if(find&&(lua_toboolean(L,4)||
strpbrk(p,"^$*+?.([%-")==NULL)){
const char*s2=lmemfind(s+init,l1-init,p,l2);
if(s2){
lua_pushinteger(L,s2-s+1);
lua_pushinteger(L,s2-s+l2);
return 2;
}
}
else{
MatchState ms;
int anchor=(*p=='^')?(p++,1):0;
const char*s1=s+init;
ms.L=L;
ms.src_init=s;
ms.src_end=s+l1;
do{
const char*res;
ms.level=0;
if((res=match(&ms,s1,p))!=NULL){
if(find){
lua_pushinteger(L,s1-s+1);
lua_pushinteger(L,res-s);
return push_captures(&ms,NULL,0)+2;
}
else
return push_captures(&ms,s1,res);
}
}while(s1++<ms.src_end&&!anchor);
}
lua_pushnil(L);
return 1;
}
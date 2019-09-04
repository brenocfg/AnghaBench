#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {size_t p; int /*<<< orphan*/  lvl; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ luaL_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  adjuststack (TYPE_1__*) ; 
 size_t bufffree (TYPE_1__*) ; 
 scalar_t__ emptybuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 

__attribute__((used)) static void luaL_addvalue(luaL_Buffer*B){
lua_State*L=B->L;
size_t vl;
const char*s=lua_tolstring(L,-1,&vl);
if(vl<=bufffree(B)){
memcpy(B->p,s,vl);
B->p+=vl;
lua_pop(L,1);
}
else{
if(emptybuffer(B))
lua_insert(L,-2);
B->lvl++;
adjuststack(B);
}
}
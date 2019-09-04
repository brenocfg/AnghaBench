#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_5__ {int level; int src_init; TYPE_1__* capture; int /*<<< orphan*/  L; } ;
struct TYPE_4__ {int len; char const* init; } ;
typedef  TYPE_2__ MatchState ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void push_onecapture(MatchState*ms,int i,const char*s,
const char*e){
if(i>=ms->level){
if(i==0)
lua_pushlstring(ms->L,s,e-s);
else
luaL_error(ms->L,"invalid capture index");
}
else{
ptrdiff_t l=ms->capture[i].len;
if(l==(-1))luaL_error(ms->L,"unfinished capture");
if(l==(-2))
lua_pushinteger(ms->L,ms->capture[i].init-ms->src_init+1);
else
lua_pushlstring(ms->L,ms->capture[i].init,l);
}
}
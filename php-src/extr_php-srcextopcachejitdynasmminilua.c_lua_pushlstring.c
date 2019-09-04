#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luaC_checkGC (TYPE_1__*) ; 
 int /*<<< orphan*/  luaS_newlstr (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  setsvalue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_pushlstring(lua_State*L,const char*s,size_t len){
luaC_checkGC(L);
setsvalue(L,L->top,luaS_newlstr(L,s,len));
api_incr_top(L);
}
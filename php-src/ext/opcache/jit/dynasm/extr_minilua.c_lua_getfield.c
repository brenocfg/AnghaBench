#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_checkvalidindex (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaS_new (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  luaV_gettable (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsvalue (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_getfield(lua_State*L,int idx,const char*k){
StkId t;
TValue key;
t=index2adr(L,idx);
api_checkvalidindex(L,t);
setsvalue(L,&key,luaS_new(L,k));
luaV_gettable(L,t,&key,L->top);
api_incr_top(L);
}
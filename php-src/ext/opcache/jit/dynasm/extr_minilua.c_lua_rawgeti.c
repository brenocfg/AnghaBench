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
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  hvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index2adr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaH_getnum (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  luai_apicheck (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttistable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lua_rawgeti(lua_State*L,int idx,int n){
StkId o;
o=index2adr(L,idx);
luai_apicheck(L,ttistable(o));
setobj(L,L->top,luaH_getnum(hvalue(o),n));
api_incr_top(L);
}
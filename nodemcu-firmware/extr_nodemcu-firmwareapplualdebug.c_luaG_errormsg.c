#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ errfunc; scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_ERRERR ; 
 int /*<<< orphan*/  LUA_ERRRUN ; 
 int /*<<< orphan*/  incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luaD_call (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  luaD_throw (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ restorestack (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ttisfunction (scalar_t__) ; 
 int /*<<< orphan*/  ttislightfunction (scalar_t__) ; 

void luaG_errormsg (lua_State *L) {
  if (L->errfunc != 0) {  /* is there an error handling function? */
    StkId errfunc = restorestack(L, L->errfunc);
    if (!ttisfunction(errfunc) && !ttislightfunction(errfunc)) luaD_throw(L, LUA_ERRERR);
    setobjs2s(L, L->top, L->top - 1);  /* move argument */
    setobjs2s(L, L->top - 1, errfunc);  /* push function */
    incr_top(L);
    luaD_call(L, L->top - 2, 1);  /* call it */
  }
  luaD_throw(L, LUA_ERRRUN);
}
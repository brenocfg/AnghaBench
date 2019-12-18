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
struct TYPE_7__ {scalar_t__ top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  scalar_t__ StkId ;

/* Variables and functions */
 int /*<<< orphan*/  TM_CALL ; 
 int /*<<< orphan*/  luaG_typeerror (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/ * luaT_gettmbyobj (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setobj2s (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  setobjs2s (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ttisfunction (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void tryfuncTM (lua_State *L, StkId func) {
  const TValue *tm = luaT_gettmbyobj(L, func, TM_CALL);
  StkId p;
  if (!ttisfunction(tm))
    luaG_typeerror(L, func, "call");
  /* Open a hole inside the stack at 'func' */
  for (p = L->top; p > func; p--)
    setobjs2s(L, p, p-1);
  L->top++;  /* slot ensured by caller */
  setobj2s(L, func, tm);  /* tag method is the new function to be called */
}
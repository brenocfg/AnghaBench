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
struct TYPE_4__ {int stack_last; int stack; int stacksize; int size_ci; scalar_t__ base_ci; scalar_t__ ci; } ;
typedef  TYPE_1__ lua_State ;

/* Variables and functions */
 int EXTRA_STACK ; 
 int LUAI_MAXCALLS ; 
 int cast_int (scalar_t__) ; 
 int /*<<< orphan*/  luaD_reallocCI (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void restore_stack_limit (lua_State *L) {
  lua_assert(L->stack_last - L->stack == L->stacksize - EXTRA_STACK - 1);
  if (L->size_ci > LUAI_MAXCALLS) {  /* there was an overflow? */
    int inuse = cast_int(L->ci - L->base_ci);
    if (inuse + 1 < LUAI_MAXCALLS)  /* can `undo' overflow? */
      luaD_reallocCI(L, LUAI_MAXCALLS);
  }
}
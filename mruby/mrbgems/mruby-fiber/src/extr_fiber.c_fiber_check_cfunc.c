#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {TYPE_1__* cibase; TYPE_1__* ci; } ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_2__ {scalar_t__ acc; } ;
typedef  TYPE_1__ mrb_callinfo ;

/* Variables and functions */
 int /*<<< orphan*/  E_FIBER_ERROR ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fiber_check_cfunc(mrb_state *mrb, struct mrb_context *c)
{
  mrb_callinfo *ci;

  for (ci = c->ci; ci >= c->cibase; ci--) {
    if (ci->acc < 0) {
      mrb_raise(mrb, E_FIBER_ERROR, "can't cross C function boundary");
    }
  }
}
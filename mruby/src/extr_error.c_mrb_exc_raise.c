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
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_7__ {int /*<<< orphan*/  jmp; int /*<<< orphan*/  eException_class; int /*<<< orphan*/  exc; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  MRB_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ mrb_break_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_p (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

void
mrb_exc_raise(mrb_state *mrb, mrb_value exc)
{
  if (mrb_break_p(exc)) {
    mrb->exc = mrb_obj_ptr(exc);
  }
  else {
    if (!mrb_obj_is_kind_of(mrb, exc, mrb->eException_class)) {
      mrb_raise(mrb, E_TYPE_ERROR, "exception object expected");
    }
    mrb_exc_set(mrb, exc);
  }
  if (!mrb->jmp) {
    mrb_p(mrb, exc);
    abort();
  }
  MRB_THROW(mrb->jmp);
}
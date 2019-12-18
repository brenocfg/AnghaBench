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
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_6__ {scalar_t__ exc; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ mrb_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_print_error (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_top_self (TYPE_1__*) ; 

__attribute__((used)) static int
eval_test(mrb_state *mrb)
{
  /* evaluate the test */
  mrb_value result = mrb_funcall(mrb, mrb_top_self(mrb), "report", 0);
  /* did an exception occur? */
  if (mrb->exc) {
    mrb_print_error(mrb);
    mrb->exc = 0;
    return EXIT_FAILURE;
  }
  else {
    return mrb_bool(result) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
}
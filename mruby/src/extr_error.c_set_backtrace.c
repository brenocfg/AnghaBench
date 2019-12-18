#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
set_backtrace(mrb_state *mrb, mrb_value exc, mrb_value backtrace)
{
  if (!mrb_array_p(backtrace)) {
  type_err:
    mrb_raise(mrb, E_TYPE_ERROR, "backtrace must be Array of String");
  }
  else {
    const mrb_value *p = RARRAY_PTR(backtrace);
    const mrb_value *pend = p + RARRAY_LEN(backtrace);

    while (p < pend) {
      if (!mrb_string_p(*p)) goto type_err;
      p++;
    }
  }
  mrb_iv_set(mrb, exc, mrb_intern_lit(mrb, "backtrace"), backtrace);
}
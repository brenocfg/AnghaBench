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
typedef  int mrb_int ;
typedef  double mrb_float ;

/* Variables and functions */
 int /*<<< orphan*/  domain_error (int /*<<< orphan*/ *,char*) ; 
 double log (double) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,double) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,double*,double*) ; 

__attribute__((used)) static mrb_value
math_log(mrb_state *mrb, mrb_value obj)
{
  mrb_float x, base;
  mrb_int argc;

  argc = mrb_get_args(mrb, "f|f", &x, &base);
  if (x < 0.0) {
    domain_error(mrb, "log");
  }
  x = log(x);
  if (argc == 2) {
    if (base < 0.0) {
      domain_error(mrb, "log");
    }
    x /= log(base);
  }
  return mrb_float_value(mrb, x);
}
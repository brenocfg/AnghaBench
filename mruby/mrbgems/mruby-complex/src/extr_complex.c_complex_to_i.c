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
struct mrb_complex {scalar_t__ imaginary; int /*<<< orphan*/  real; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 struct mrb_complex* complex_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_int_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
complex_to_i(mrb_state *mrb, mrb_value self)
{
  struct mrb_complex *p = complex_ptr(mrb, self);

  if (p->imaginary != 0) {
    mrb_raisef(mrb, E_RANGE_ERROR, "can't convert %v into Float", self);
  }
  return mrb_int_value(mrb, p->real);
}
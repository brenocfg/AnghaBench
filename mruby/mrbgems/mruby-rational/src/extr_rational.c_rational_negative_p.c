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
struct mrb_rational {scalar_t__ numerator; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 struct mrb_rational* rational_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
rational_negative_p(mrb_state *mrb, mrb_value self)
{
  struct mrb_rational *p = rational_ptr(mrb, self);
  if (p->numerator < 0) {
    return mrb_true_value();
  }
  return mrb_false_value();
}
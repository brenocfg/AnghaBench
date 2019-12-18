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
struct mrb_rational {void* denominator; void* numerator; } ;
struct RClass {int dummy; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  void* mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_SET_FROZEN_FLAG (struct RBasic*) ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RBasic*) ; 
 struct RBasic* rational_alloc (int /*<<< orphan*/ *,struct RClass*,struct mrb_rational**) ; 

__attribute__((used)) static mrb_value
rational_new(mrb_state *mrb, mrb_int numerator, mrb_int denominator)
{
  struct RClass *c = mrb_class_get(mrb, "Rational");
  struct mrb_rational *p;
  struct RBasic *rat = rational_alloc(mrb, c, &p);
  p->numerator = numerator;
  p->denominator = denominator;
  MRB_SET_FROZEN_FLAG(rat);
  return mrb_obj_value(rat);
}
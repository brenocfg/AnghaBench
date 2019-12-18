#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mrb_rational {int dummy; } ;
struct RClass {int dummy; } ;
struct TYPE_8__ {struct RClass* fixnum_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int ISTRUCT_DATA_SIZE ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  MRB_TT_ISTRUCT ; 
 int /*<<< orphan*/  fix_to_r ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_class_get (TYPE_1__*,char*) ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_class_method (TYPE_1__*,struct RClass*,char*) ; 
 int /*<<< orphan*/  rational_denominator ; 
 int /*<<< orphan*/  rational_negative_p ; 
 int /*<<< orphan*/  rational_numerator ; 
 int /*<<< orphan*/  rational_s_new ; 
 int /*<<< orphan*/  rational_to_f ; 
 int /*<<< orphan*/  rational_to_i ; 
 int /*<<< orphan*/  rational_to_r ; 

void mrb_mruby_rational_gem_init(mrb_state *mrb)
{
  struct RClass *rat;

  rat = mrb_define_class(mrb, "Rational", mrb_class_get(mrb, "Numeric"));
#ifdef RATIONAL_USE_ISTRUCT
  MRB_SET_INSTANCE_TT(rat, MRB_TT_ISTRUCT);
  mrb_assert(sizeof(struct mrb_rational) < ISTRUCT_DATA_SIZE);
#else
  MRB_SET_INSTANCE_TT(rat, MRB_TT_DATA);
#endif
  mrb_undef_class_method(mrb, rat, "new");
  mrb_define_class_method(mrb, rat, "_new", rational_s_new, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, rat, "numerator", rational_numerator, MRB_ARGS_NONE());
  mrb_define_method(mrb, rat, "denominator", rational_denominator, MRB_ARGS_NONE());
#ifndef MRB_WITHOUT_FLOAT
  mrb_define_method(mrb, rat, "to_f", rational_to_f, MRB_ARGS_NONE());
#endif
  mrb_define_method(mrb, rat, "to_i", rational_to_i, MRB_ARGS_NONE());
  mrb_define_method(mrb, rat, "to_r", rational_to_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, rat, "negative?", rational_negative_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, mrb->fixnum_class, "to_r", fix_to_r, MRB_ARGS_NONE());
}
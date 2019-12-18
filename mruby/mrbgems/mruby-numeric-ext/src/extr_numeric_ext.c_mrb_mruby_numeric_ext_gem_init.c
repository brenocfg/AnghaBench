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
struct RClass {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  float_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_FLT_DIG ; 
 int /*<<< orphan*/  MRB_FLT_EPSILON ; 
 int /*<<< orphan*/  MRB_FLT_MANT_DIG ; 
 int /*<<< orphan*/  MRB_FLT_MAX ; 
 int /*<<< orphan*/  MRB_FLT_MAX_10_EXP ; 
 int /*<<< orphan*/  MRB_FLT_MAX_EXP ; 
 int /*<<< orphan*/  MRB_FLT_MIN ; 
 int /*<<< orphan*/  MRB_FLT_MIN_10_EXP ; 
 int /*<<< orphan*/  MRB_FLT_MIN_EXP ; 
 int /*<<< orphan*/  MRB_FLT_RADIX ; 
 int /*<<< orphan*/  mrb_define_const (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float_value (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_int_allbits ; 
 int /*<<< orphan*/  mrb_int_anybits ; 
 int /*<<< orphan*/  mrb_int_nobits ; 
 struct RClass* mrb_module_get (TYPE_1__*,char*) ; 

void
mrb_mruby_numeric_ext_gem_init(mrb_state* mrb)
{
  struct RClass *i = mrb_module_get(mrb, "Integral");

  mrb_define_method(mrb, i, "allbits?", mrb_int_allbits, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, i, "anybits?", mrb_int_anybits, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, i, "nobits?", mrb_int_nobits, MRB_ARGS_REQ(1));

#ifndef MRB_WITHOUT_FLOAT
  mrb_define_const(mrb, mrb->float_class, "RADIX",        mrb_fixnum_value(MRB_FLT_RADIX));
  mrb_define_const(mrb, mrb->float_class, "MANT_DIG",     mrb_fixnum_value(MRB_FLT_MANT_DIG));
  mrb_define_const(mrb, mrb->float_class, "EPSILON",      mrb_float_value(mrb, MRB_FLT_EPSILON));
  mrb_define_const(mrb, mrb->float_class, "DIG",          mrb_fixnum_value(MRB_FLT_DIG));
  mrb_define_const(mrb, mrb->float_class, "MIN_EXP",      mrb_fixnum_value(MRB_FLT_MIN_EXP));
  mrb_define_const(mrb, mrb->float_class, "MIN",          mrb_float_value(mrb, MRB_FLT_MIN));
  mrb_define_const(mrb, mrb->float_class, "MIN_10_EXP",   mrb_fixnum_value(MRB_FLT_MIN_10_EXP));
  mrb_define_const(mrb, mrb->float_class, "MAX_EXP",      mrb_fixnum_value(MRB_FLT_MAX_EXP));
  mrb_define_const(mrb, mrb->float_class, "MAX",          mrb_float_value(mrb, MRB_FLT_MAX));
  mrb_define_const(mrb, mrb->float_class, "MAX_10_EXP",   mrb_fixnum_value(MRB_FLT_MAX_10_EXP));
#endif /* MRB_WITHOUT_FLOAT */
}
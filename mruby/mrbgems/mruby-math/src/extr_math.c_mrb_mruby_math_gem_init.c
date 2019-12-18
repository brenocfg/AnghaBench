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
struct RClass {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  eStandardError_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 double M_E ; 
 double M_PI ; 
 double atan (double) ; 
 double exp (double) ; 
 int /*<<< orphan*/  math_acos ; 
 int /*<<< orphan*/  math_acosh ; 
 int /*<<< orphan*/  math_asin ; 
 int /*<<< orphan*/  math_asinh ; 
 int /*<<< orphan*/  math_atan ; 
 int /*<<< orphan*/  math_atan2 ; 
 int /*<<< orphan*/  math_atanh ; 
 int /*<<< orphan*/  math_cbrt ; 
 int /*<<< orphan*/  math_cos ; 
 int /*<<< orphan*/  math_cosh ; 
 int /*<<< orphan*/  math_erf ; 
 int /*<<< orphan*/  math_erfc ; 
 int /*<<< orphan*/  math_exp ; 
 int /*<<< orphan*/  math_frexp ; 
 int /*<<< orphan*/  math_hypot ; 
 int /*<<< orphan*/  math_ldexp ; 
 int /*<<< orphan*/  math_log ; 
 int /*<<< orphan*/  math_log10 ; 
 int /*<<< orphan*/  math_log2 ; 
 int /*<<< orphan*/  math_sin ; 
 int /*<<< orphan*/  math_sinh ; 
 int /*<<< orphan*/  math_sqrt ; 
 int /*<<< orphan*/  math_tan ; 
 int /*<<< orphan*/  math_tanh ; 
 int /*<<< orphan*/  mrb_define_class_under (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_const (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_float_value (TYPE_1__*,double) ; 

void
mrb_mruby_math_gem_init(mrb_state* mrb)
{
  struct RClass *mrb_math;
  mrb_math = mrb_define_module(mrb, "Math");

  mrb_define_class_under(mrb, mrb_math, "DomainError", mrb->eStandardError_class);

#ifdef M_PI
  mrb_define_const(mrb, mrb_math, "PI", mrb_float_value(mrb, M_PI));
#else
  mrb_define_const(mrb, mrb_math, "PI", mrb_float_value(mrb, atan(1.0)*4.0));
#endif

#ifdef M_E
  mrb_define_const(mrb, mrb_math, "E", mrb_float_value(mrb, M_E));
#else
  mrb_define_const(mrb, mrb_math, "E", mrb_float_value(mrb, exp(1.0)));
#endif

  mrb_define_module_function(mrb, mrb_math, "sin", math_sin, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "cos", math_cos, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "tan", math_tan, MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, mrb_math, "asin", math_asin, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "acos", math_acos, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "atan", math_atan, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "atan2", math_atan2, MRB_ARGS_REQ(2));

  mrb_define_module_function(mrb, mrb_math, "sinh", math_sinh, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "cosh", math_cosh, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "tanh", math_tanh, MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, mrb_math, "asinh", math_asinh, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "acosh", math_acosh, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "atanh", math_atanh, MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, mrb_math, "exp", math_exp, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "log", math_log, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_module_function(mrb, mrb_math, "log2", math_log2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "log10", math_log10, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "sqrt", math_sqrt, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "cbrt", math_cbrt, MRB_ARGS_REQ(1));

  mrb_define_module_function(mrb, mrb_math, "frexp", math_frexp, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "ldexp", math_ldexp, MRB_ARGS_REQ(2));

  mrb_define_module_function(mrb, mrb_math, "hypot", math_hypot, MRB_ARGS_REQ(2));

  mrb_define_module_function(mrb, mrb_math, "erf",  math_erf,  MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_math, "erfc", math_erfc, MRB_ARGS_REQ(1));
}
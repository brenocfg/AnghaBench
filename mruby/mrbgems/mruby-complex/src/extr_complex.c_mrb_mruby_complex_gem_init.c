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
struct mrb_complex {int dummy; } ;
struct RClass {int dummy; } ;
struct TYPE_8__ {struct RClass* kernel_module; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int ISTRUCT_DATA_SIZE ; 
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_OPT (int) ; 
 int MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_DATA ; 
 int /*<<< orphan*/  MRB_TT_ISTRUCT ; 
 int /*<<< orphan*/  complex_div ; 
 int /*<<< orphan*/  complex_imaginary ; 
 int /*<<< orphan*/  complex_real ; 
 int /*<<< orphan*/  complex_s_rect ; 
 int /*<<< orphan*/  complex_to_c ; 
 int /*<<< orphan*/  complex_to_f ; 
 int /*<<< orphan*/  complex_to_i ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_class_get (TYPE_1__*,char*) ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_undef_class_method (TYPE_1__*,struct RClass*,char*) ; 

void mrb_mruby_complex_gem_init(mrb_state *mrb)
{
  struct RClass *comp;

#ifdef COMPLEX_USE_ISTRUCT
  mrb_assert(sizeof(struct mrb_complex) < ISTRUCT_DATA_SIZE);
#endif
  comp = mrb_define_class(mrb, "Complex", mrb_class_get(mrb, "Numeric"));
#ifdef COMPLEX_USE_ISTRUCT
  MRB_SET_INSTANCE_TT(comp, MRB_TT_ISTRUCT);
#else
  MRB_SET_INSTANCE_TT(comp, MRB_TT_DATA);
#endif
  mrb_undef_class_method(mrb, comp, "new");
  mrb_define_class_method(mrb, comp, "rectangular", complex_s_rect, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, comp, "rect", complex_s_rect, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_method(mrb, mrb->kernel_module, "Complex", complex_s_rect, MRB_ARGS_REQ(1)|MRB_ARGS_OPT(1));
  mrb_define_method(mrb, comp, "real", complex_real, MRB_ARGS_NONE());
  mrb_define_method(mrb, comp, "imaginary", complex_imaginary, MRB_ARGS_NONE());
  mrb_define_method(mrb, comp, "to_f", complex_to_f, MRB_ARGS_NONE());
  mrb_define_method(mrb, comp, "to_i", complex_to_i, MRB_ARGS_NONE());
  mrb_define_method(mrb, comp, "to_c", complex_to_c, MRB_ARGS_NONE());
  mrb_define_method(mrb, comp, "__div__", complex_div, MRB_ARGS_REQ(1));
}
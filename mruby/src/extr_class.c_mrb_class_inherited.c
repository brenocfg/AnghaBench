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
struct RClass {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
struct TYPE_7__ {struct RClass* object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_FL_CLASS_IS_INHERITED ; 
 int /*<<< orphan*/  mc_clear_by_class (TYPE_1__*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_bob_init ; 
 int /*<<< orphan*/  mrb_func_basic_p (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall_argv (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

__attribute__((used)) static void
mrb_class_inherited(mrb_state *mrb, struct RClass *super, struct RClass *klass)
{
  mrb_value s;
  mrb_sym mid;

  if (!super)
    super = mrb->object_class;
  super->flags |= MRB_FL_CLASS_IS_INHERITED;
  s = mrb_obj_value(super);
  mc_clear_by_class(mrb, klass);
  mid = mrb_intern_lit(mrb, "inherited");
  if (!mrb_func_basic_p(mrb, s, mid, mrb_bob_init)) {
    mrb_value c = mrb_obj_value(klass);
    mrb_funcall_argv(mrb, s, mid, 1, &c);
  }
}
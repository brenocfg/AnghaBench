#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_ISTRUCT ; 
 int /*<<< orphan*/  istruct_test_initialize ; 
 int /*<<< orphan*/  istruct_test_length ; 
 int /*<<< orphan*/  istruct_test_mutate ; 
 int /*<<< orphan*/  istruct_test_test_receive ; 
 int /*<<< orphan*/  istruct_test_test_receive_direct ; 
 int /*<<< orphan*/  istruct_test_to_s ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mrb_mruby_inline_struct_gem_test(mrb_state *mrb)
{
  struct RClass *cls;

  cls = mrb_define_class(mrb, "InlineStructTest", mrb->object_class);
  MRB_SET_INSTANCE_TT(cls, MRB_TT_ISTRUCT);
  mrb_define_method(mrb, cls, "initialize", istruct_test_initialize, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cls, "to_s", istruct_test_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cls, "mutate", istruct_test_mutate, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cls, "length", istruct_test_length, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cls, "test_receive", istruct_test_test_receive, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, cls, "test_receive_direct", istruct_test_test_receive_direct, MRB_ARGS_REQ(1));
}
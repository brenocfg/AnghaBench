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
struct TYPE_6__ {struct RClass* module_class; struct RClass* kernel_module; int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int MRB_ARGS_ANY () ; 
 int MRB_ARGS_NONE () ; 
 int MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  method_arity ; 
 int /*<<< orphan*/  method_bcall ; 
 int /*<<< orphan*/  method_call ; 
 int /*<<< orphan*/  method_eql ; 
 int /*<<< orphan*/  method_name ; 
 int /*<<< orphan*/  method_owner ; 
 int /*<<< orphan*/  method_parameters ; 
 int /*<<< orphan*/  method_receiver ; 
 int /*<<< orphan*/  method_source_location ; 
 int /*<<< orphan*/  method_super_method ; 
 int /*<<< orphan*/  method_to_s ; 
 int /*<<< orphan*/  method_unbind ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_kernel_method ; 
 int /*<<< orphan*/  mrb_module_instance_method ; 
 int /*<<< orphan*/  mrb_undef_class_method (TYPE_1__*,struct RClass*,char*) ; 
 int /*<<< orphan*/  unbound_method_bind ; 

void
mrb_mruby_method_gem_init(mrb_state* mrb)
{
  struct RClass *unbound_method = mrb_define_class(mrb, "UnboundMethod", mrb->object_class);
  struct RClass *method = mrb_define_class(mrb, "Method", mrb->object_class);

  mrb_undef_class_method(mrb, unbound_method, "new");
  mrb_define_method(mrb, unbound_method, "bind", unbound_method_bind, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, unbound_method, "super_method", method_super_method, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "==", method_eql, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, unbound_method, "eql?", method_eql, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, unbound_method, "to_s", method_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "inspect", method_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "arity", method_arity, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "source_location", method_source_location, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "parameters", method_parameters, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "bind_call", method_bcall, MRB_ARGS_REQ(1)|MRB_ARGS_ANY());
  mrb_define_method(mrb, unbound_method, "owner", method_owner, MRB_ARGS_NONE());
  mrb_define_method(mrb, unbound_method, "name", method_name, MRB_ARGS_NONE());

  mrb_undef_class_method(mrb, method, "new");
  mrb_define_method(mrb, method, "==", method_eql, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, method, "eql?", method_eql, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, method, "to_s", method_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "inspect", method_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "call", method_call, MRB_ARGS_ANY());
  mrb_define_method(mrb, method, "[]", method_call, MRB_ARGS_ANY());
  mrb_define_method(mrb, method, "unbind", method_unbind, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "super_method", method_super_method, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "arity", method_arity, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "source_location", method_source_location, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "parameters", method_parameters, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "owner", method_owner, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "receiver", method_receiver, MRB_ARGS_NONE());
  mrb_define_method(mrb, method, "name", method_name, MRB_ARGS_NONE());

  mrb_define_method(mrb, mrb->kernel_module, "method", mrb_kernel_method, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb->module_class, "instance_method", mrb_module_instance_method, MRB_ARGS_REQ(1));
}
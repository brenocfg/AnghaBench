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
struct TYPE_6__ {int /*<<< orphan*/  kernel_module; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int) ; 
 int MRB_ARGS_BLOCK () ; 
 int MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  f_eval ; 
 int /*<<< orphan*/  f_instance_eval ; 
 int /*<<< orphan*/  mrb_class_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_define_module_function (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_mruby_eval_gem_init(mrb_state* mrb)
{
  mrb_define_module_function(mrb, mrb->kernel_module, "eval", f_eval, MRB_ARGS_ARG(1, 3));
  mrb_define_method(mrb, mrb_class_get(mrb, "BasicObject"), "instance_eval", f_instance_eval, MRB_ARGS_OPT(3)|MRB_ARGS_BLOCK());
}
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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 scalar_t__ mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_module_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_sclass_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bind_check(mrb_state *mrb, mrb_value recv, mrb_value owner)
{
  if (!mrb_module_p(owner) &&
      mrb_class_ptr(owner) != mrb_obj_class(mrb, recv) &&
      !mrb_obj_is_kind_of(mrb, recv, mrb_class_ptr(owner))) {
    if (mrb_sclass_p(owner)) {
      mrb_raise(mrb, E_TYPE_ERROR, "singleton method called for a different object");
    } else {
      mrb_raisef(mrb, E_TYPE_ERROR, "bind argument must be an instance of %v", owner);
    }
  }
}
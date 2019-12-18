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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  check_if_class_or_module (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RClass* define_module (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RClass*) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_const_defined_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_module_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct RClass*
mrb_vm_define_module(mrb_state *mrb, mrb_value outer, mrb_sym id)
{
  check_if_class_or_module(mrb, outer);
  if (mrb_const_defined_at(mrb, outer, id)) {
    mrb_value old = mrb_const_get(mrb, outer, id);

    if (!mrb_module_p(old)) {
      mrb_raisef(mrb, E_TYPE_ERROR, "%!v is not a module", old);
    }
    return mrb_class_ptr(old);
  }
  return define_module(mrb, id, mrb_class_ptr(outer));
}
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
 int /*<<< orphan*/  mrb_bool_value (int) ; 
 scalar_t__ mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_istruct_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
istruct_test_test_receive(mrb_state *mrb, mrb_value self)
{
  mrb_value object;
  mrb_get_args(mrb, "o", &object);
  if (mrb_obj_class(mrb, object) != mrb_class_get(mrb, "InlineStructTest"))
  {
    mrb_raise(mrb, E_TYPE_ERROR, "Expected InlineStructTest");
  }
  return mrb_bool_value(((char*)mrb_istruct_ptr(object))[0] == 's');
}
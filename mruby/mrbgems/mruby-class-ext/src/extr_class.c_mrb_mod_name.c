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
 int /*<<< orphan*/  MRB_SET_FROZEN_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_basic_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_mod_name(mrb_state *mrb, mrb_value self)
{
  mrb_value name =  mrb_class_path(mrb, mrb_class_ptr(self));
  if (mrb_string_p(name)) {
    MRB_SET_FROZEN_FLAG(mrb_basic_ptr(name));
  }
  return name;
}
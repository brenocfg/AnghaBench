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
struct os_each_object_data {scalar_t__ count; int /*<<< orphan*/ * target_module; int /*<<< orphan*/  block; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/ * mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_objspace_each_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct os_each_object_data*) ; 
 int /*<<< orphan*/  os_each_object_cb ; 

__attribute__((used)) static mrb_value
os_each_object(mrb_state *mrb, mrb_value self)
{
  mrb_value cls = mrb_nil_value();
  struct os_each_object_data d;
  mrb_get_args(mrb, "&!|C", &d.block, &cls);

  d.target_module = mrb_nil_p(cls) ? NULL : mrb_class_ptr(cls);
  d.count = 0;
  mrb_objspace_each_objects(mrb, os_each_object_cb, &d);
  return mrb_fixnum_value(d.count);
}
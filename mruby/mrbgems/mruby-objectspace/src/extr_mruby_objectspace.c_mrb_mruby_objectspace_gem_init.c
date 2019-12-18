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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  os_count_objects ; 
 int /*<<< orphan*/  os_each_object ; 

void
mrb_mruby_objectspace_gem_init(mrb_state *mrb)
{
  struct RClass *os = mrb_define_module(mrb, "ObjectSpace");
  mrb_define_class_method(mrb, os, "count_objects", os_count_objects, MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, os, "each_object", os_each_object, MRB_ARGS_OPT(1));
}
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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ mrb_class_defined (int /*<<< orphan*/ *,char*) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 scalar_t__ mrb_const_defined (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (int /*<<< orphan*/ *,char*) ; 
 struct RClass* mrb_module_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

__attribute__((used)) static void
io_set_process_status(mrb_state *mrb, pid_t pid, int status)
{
  struct RClass *c_process, *c_status;
  mrb_value v;

  c_status = NULL;
  if (mrb_class_defined(mrb, "Process")) {
    c_process = mrb_module_get(mrb, "Process");
    if (mrb_const_defined(mrb, mrb_obj_value(c_process), mrb_intern_cstr(mrb, "Status"))) {
      c_status = mrb_class_get_under(mrb, c_process, "Status");
    }
  }
  if (c_status != NULL) {
    v = mrb_funcall(mrb, mrb_obj_value(c_status), "new", 2, mrb_fixnum_value(pid), mrb_fixnum_value(status));
  } else {
    v = mrb_fixnum_value(WEXITSTATUS(status));
  }
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$?"), v);
}
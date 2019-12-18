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
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mrb_define_class_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_io_test_file_cleanup ; 
 int /*<<< orphan*/  mrb_io_test_file_setup ; 
 int /*<<< orphan*/  mrb_io_test_io_cleanup ; 
 int /*<<< orphan*/  mrb_io_test_io_setup ; 
 int /*<<< orphan*/  mrb_io_test_mkdtemp ; 
 int /*<<< orphan*/  mrb_io_test_rmdir ; 
 int /*<<< orphan*/  mrb_io_win_p ; 

void
mrb_mruby_io_gem_test(mrb_state* mrb)
{
  struct RClass *io_test = mrb_define_module(mrb, "MRubyIOTestUtil");
  mrb_define_class_method(mrb, io_test, "io_test_setup", mrb_io_test_io_setup, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, io_test, "io_test_cleanup", mrb_io_test_io_cleanup, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, io_test, "file_test_setup", mrb_io_test_file_setup, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, io_test, "file_test_cleanup", mrb_io_test_file_cleanup, MRB_ARGS_NONE());

  mrb_define_class_method(mrb, io_test, "mkdtemp", mrb_io_test_mkdtemp, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, io_test, "rmdir", mrb_io_test_rmdir, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, io_test, "win?", mrb_io_win_p, MRB_ARGS_NONE());
}
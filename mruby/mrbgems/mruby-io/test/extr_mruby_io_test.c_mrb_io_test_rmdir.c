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
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int rmdir (char const*) ; 

__attribute__((used)) static mrb_value
mrb_io_test_rmdir(mrb_state *mrb, mrb_value klass)
{
  const char *cp;

  mrb_get_args(mrb, "z", &cp);
  if (rmdir(cp) == -1) {
    mrb_sys_fail(mrb, "rmdir");
  }
  return mrb_true_value();
}
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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  DONE ; 
 int /*<<< orphan*/  mrb_init_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_file_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_init_io (int /*<<< orphan*/ *) ; 

void
mrb_mruby_io_gem_init(mrb_state* mrb)
{
  mrb_init_io(mrb); DONE;
  mrb_init_file(mrb); DONE;
  mrb_init_file_test(mrb); DONE;
}
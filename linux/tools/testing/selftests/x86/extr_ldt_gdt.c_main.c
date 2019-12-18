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

/* Variables and functions */
 int /*<<< orphan*/  do_exec_test () ; 
 int /*<<< orphan*/  do_multicpu_tests () ; 
 int /*<<< orphan*/  do_simple_tests () ; 
 int finish_exec_test () ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  setup_counter_page () ; 
 int /*<<< orphan*/  setup_low_user_desc () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_gdt_invalidation () ; 

int main(int argc, char **argv)
{
	if (argc == 1 && !strcmp(argv[0], "ldt_gdt_test_exec"))
		return finish_exec_test();

	setup_counter_page();
	setup_low_user_desc();

	do_simple_tests();

	do_multicpu_tests();

	do_exec_test();

	test_gdt_invalidation();

	return nerrs ? 1 : 0;
}
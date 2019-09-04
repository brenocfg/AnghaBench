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
 int /*<<< orphan*/  bounds_dir_ptr ; 
 int /*<<< orphan*/  do_one_malloc ; 
 int /*<<< orphan*/  inspect_me (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_timed_test (int /*<<< orphan*/ *) ; 

void check_bounds_table_frees(void)
{
	printf("executing unmaptest\n");
	inspect_me(bounds_dir_ptr);
	run_timed_test(&do_one_malloc);
	printf("done with malloc() fun\n");
}
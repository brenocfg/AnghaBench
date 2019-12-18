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
 int EINVAL ; 
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  check_account (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_align (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_cmpxchg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_create_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_find_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_insert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_move (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_multi_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_reserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_store_iter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_store_range (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_workingset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_xa_alloc () ; 
 int /*<<< orphan*/  check_xa_err (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_xa_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_xa_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_xa_shrink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_xas_erase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_xas_retry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ tests_passed ; 
 scalar_t__ tests_run ; 
 int /*<<< orphan*/  xa0 ; 

__attribute__((used)) static int xarray_checks(void)
{
	check_xa_err(&array);
	check_xas_retry(&array);
	check_xa_load(&array);
	check_xa_mark(&array);
	check_xa_shrink(&array);
	check_xas_erase(&array);
	check_insert(&array);
	check_cmpxchg(&array);
	check_reserve(&array);
	check_reserve(&xa0);
	check_multi_store(&array);
	check_xa_alloc();
	check_find(&array);
	check_find_entry(&array);
	check_account(&array);
	check_destroy(&array);
	check_move(&array);
	check_create_range(&array);
	check_store_range(&array);
	check_store_iter(&array);
	check_align(&xa0);

	check_workingset(&array, 0);
	check_workingset(&array, 64);
	check_workingset(&array, 4096);

	printk("XArray: %u of %u tests passed\n", tests_passed, tests_run);
	return (tests_run == tests_passed) ? 0 : -EINVAL;
}
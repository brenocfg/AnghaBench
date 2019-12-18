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
 int /*<<< orphan*/  IDA_BUG_ON (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ida ; 
 int /*<<< orphan*/  ida_check_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_check_conv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_check_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_check_leaf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ida_check_max (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ tests_passed ; 
 scalar_t__ tests_run ; 

__attribute__((used)) static int ida_checks(void)
{
	IDA_BUG_ON(&ida, !ida_is_empty(&ida));
	ida_check_alloc(&ida);
	ida_check_destroy(&ida);
	ida_check_leaf(&ida, 0);
	ida_check_leaf(&ida, 1024);
	ida_check_leaf(&ida, 1024 * 64);
	ida_check_max(&ida);
	ida_check_conv(&ida);

	printk("IDA: %u of %u tests passed\n", tests_passed, tests_run);
	return (tests_run != tests_passed) ? 0 : -EINVAL;
}
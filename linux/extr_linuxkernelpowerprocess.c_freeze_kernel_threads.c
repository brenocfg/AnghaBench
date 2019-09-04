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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_atomic () ; 
 int pm_nosig_freezing ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  thaw_kernel_threads () ; 
 int try_to_freeze_tasks (int) ; 

int freeze_kernel_threads(void)
{
	int error;

	pr_info("Freezing remaining freezable tasks ... ");

	pm_nosig_freezing = true;
	error = try_to_freeze_tasks(false);
	if (!error)
		pr_cont("done.");

	pr_cont("\n");
	BUG_ON(in_atomic());

	if (error)
		thaw_kernel_threads();
	return error;
}
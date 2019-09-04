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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XEN_MC_NONURGENT ; 
 int /*<<< orphan*/  XEN_MC_URGENT ; 
 int mc_queue_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcelog_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_mce_chrdev_wait ; 

__attribute__((used)) static void xen_mce_work_fn(struct work_struct *work)
{
	int err;

	mutex_lock(&mcelog_lock);

	/* urgent mc_info */
	err = mc_queue_handle(XEN_MC_URGENT);
	if (err)
		pr_err("Failed to handle urgent mc_info queue, continue handling nonurgent mc_info queue anyway\n");

	/* nonurgent mc_info */
	err = mc_queue_handle(XEN_MC_NONURGENT);
	if (err)
		pr_err("Failed to handle nonurgent mc_info queue\n");

	/* wake processes polling /dev/mcelog */
	wake_up_interruptible(&xen_mce_chrdev_wait);

	mutex_unlock(&mcelog_lock);
}
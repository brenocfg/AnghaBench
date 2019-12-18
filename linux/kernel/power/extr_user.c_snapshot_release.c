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
struct snapshot_data {scalar_t__ mode; scalar_t__ free_bitmaps; scalar_t__ frozen; int /*<<< orphan*/  swap; } ;
struct inode {int dummy; } ;
struct file {struct snapshot_data* private_data; } ;

/* Variables and functions */
 scalar_t__ O_RDONLY ; 
 int /*<<< orphan*/  PM_POST_HIBERNATION ; 
 int /*<<< orphan*/  PM_POST_RESTORE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_all_swap_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_basic_memory_bitmaps () ; 
 int /*<<< orphan*/  lock_system_sleep () ; 
 int /*<<< orphan*/  pm_notifier_call_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_restore_gfp_mask () ; 
 int /*<<< orphan*/  snapshot_device_available ; 
 int /*<<< orphan*/  swsusp_free () ; 
 int /*<<< orphan*/  thaw_processes () ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 

__attribute__((used)) static int snapshot_release(struct inode *inode, struct file *filp)
{
	struct snapshot_data *data;

	lock_system_sleep();

	swsusp_free();
	data = filp->private_data;
	free_all_swap_pages(data->swap);
	if (data->frozen) {
		pm_restore_gfp_mask();
		free_basic_memory_bitmaps();
		thaw_processes();
	} else if (data->free_bitmaps) {
		free_basic_memory_bitmaps();
	}
	pm_notifier_call_chain(data->mode == O_RDONLY ?
			PM_POST_HIBERNATION : PM_POST_RESTORE);
	atomic_inc(&snapshot_device_available);

	unlock_system_sleep();

	return 0;
}
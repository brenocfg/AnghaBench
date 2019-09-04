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
struct snapshot_handle {int dummy; } ;
struct snapshot_data {int swap; int mode; int free_bitmaps; int frozen; int ready; int platform_support; int /*<<< orphan*/  handle; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct snapshot_data* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSYS ; 
 int EPERM ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PM_HIBERNATION_PREPARE ; 
 int /*<<< orphan*/  PM_POST_HIBERNATION ; 
 int /*<<< orphan*/  PM_POST_RESTORE ; 
 int /*<<< orphan*/  PM_RESTORE_PREPARE ; 
 int __pm_notifier_call_chain (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int create_basic_memory_bitmaps () ; 
 int /*<<< orphan*/  hibernation_available () ; 
 int /*<<< orphan*/  lock_system_sleep () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  snapshot_device_available ; 
 struct snapshot_data snapshot_state ; 
 int swap_type_of (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ swsusp_resume_device ; 
 int /*<<< orphan*/  unlock_system_sleep () ; 
 int /*<<< orphan*/  wait_for_device_probe () ; 

__attribute__((used)) static int snapshot_open(struct inode *inode, struct file *filp)
{
	struct snapshot_data *data;
	int error, nr_calls = 0;

	if (!hibernation_available())
		return -EPERM;

	lock_system_sleep();

	if (!atomic_add_unless(&snapshot_device_available, -1, 0)) {
		error = -EBUSY;
		goto Unlock;
	}

	if ((filp->f_flags & O_ACCMODE) == O_RDWR) {
		atomic_inc(&snapshot_device_available);
		error = -ENOSYS;
		goto Unlock;
	}
	nonseekable_open(inode, filp);
	data = &snapshot_state;
	filp->private_data = data;
	memset(&data->handle, 0, sizeof(struct snapshot_handle));
	if ((filp->f_flags & O_ACCMODE) == O_RDONLY) {
		/* Hibernating.  The image device should be accessible. */
		data->swap = swsusp_resume_device ?
			swap_type_of(swsusp_resume_device, 0, NULL) : -1;
		data->mode = O_RDONLY;
		data->free_bitmaps = false;
		error = __pm_notifier_call_chain(PM_HIBERNATION_PREPARE, -1, &nr_calls);
		if (error)
			__pm_notifier_call_chain(PM_POST_HIBERNATION, --nr_calls, NULL);
	} else {
		/*
		 * Resuming.  We may need to wait for the image device to
		 * appear.
		 */
		wait_for_device_probe();

		data->swap = -1;
		data->mode = O_WRONLY;
		error = __pm_notifier_call_chain(PM_RESTORE_PREPARE, -1, &nr_calls);
		if (!error) {
			error = create_basic_memory_bitmaps();
			data->free_bitmaps = !error;
		} else
			nr_calls--;

		if (error)
			__pm_notifier_call_chain(PM_POST_RESTORE, nr_calls, NULL);
	}
	if (error)
		atomic_inc(&snapshot_device_available);

	data->frozen = false;
	data->ready = false;
	data->platform_support = false;

 Unlock:
	unlock_system_sleep();

	return error;
}
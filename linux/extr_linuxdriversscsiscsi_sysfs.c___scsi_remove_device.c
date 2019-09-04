#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct scsi_device {scalar_t__ sdev_state; TYPE_2__* host; int /*<<< orphan*/  requeue_work; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  state_mutex; struct device sdev_dev; struct device sdev_gendev; scalar_t__ is_visible; } ;
struct TYPE_4__ {TYPE_1__* hostt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* slave_destroy ) (struct scsi_device*) ;scalar_t__ sdev_groups; } ;

/* Variables and functions */
 scalar_t__ SDEV_CANCEL ; 
 scalar_t__ SDEV_DEL ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsg_unregister_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int scsi_device_set_state (struct scsi_device*,scalar_t__) ; 
 int /*<<< orphan*/  scsi_start_queue (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_target_reap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_device*) ; 
 int /*<<< orphan*/  sysfs_remove_groups (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  transport_destroy_device (struct device*) ; 
 int /*<<< orphan*/  transport_remove_device (struct device*) ; 

void __scsi_remove_device(struct scsi_device *sdev)
{
	struct device *dev = &sdev->sdev_gendev;
	int res;

	/*
	 * This cleanup path is not reentrant and while it is impossible
	 * to get a new reference with scsi_device_get() someone can still
	 * hold a previously acquired one.
	 */
	if (sdev->sdev_state == SDEV_DEL)
		return;

	if (sdev->is_visible) {
		/*
		 * If scsi_internal_target_block() is running concurrently,
		 * wait until it has finished before changing the device state.
		 */
		mutex_lock(&sdev->state_mutex);
		/*
		 * If blocked, we go straight to DEL and restart the queue so
		 * any commands issued during driver shutdown (like sync
		 * cache) are errored immediately.
		 */
		res = scsi_device_set_state(sdev, SDEV_CANCEL);
		if (res != 0) {
			res = scsi_device_set_state(sdev, SDEV_DEL);
			if (res == 0)
				scsi_start_queue(sdev);
		}
		mutex_unlock(&sdev->state_mutex);

		if (res != 0)
			return;

		if (sdev->host->hostt->sdev_groups)
			sysfs_remove_groups(&sdev->sdev_gendev.kobj,
					sdev->host->hostt->sdev_groups);

		bsg_unregister_queue(sdev->request_queue);
		device_unregister(&sdev->sdev_dev);
		transport_remove_device(dev);
		device_del(dev);
	} else
		put_device(&sdev->sdev_dev);

	/*
	 * Stop accepting new requests and wait until all queuecommand() and
	 * scsi_run_queue() invocations have finished before tearing down the
	 * device.
	 */
	mutex_lock(&sdev->state_mutex);
	scsi_device_set_state(sdev, SDEV_DEL);
	mutex_unlock(&sdev->state_mutex);

	blk_cleanup_queue(sdev->request_queue);
	cancel_work_sync(&sdev->requeue_work);

	if (sdev->host->hostt->slave_destroy)
		sdev->host->hostt->slave_destroy(sdev);
	transport_destroy_device(dev);

	/*
	 * Paired with the kref_get() in scsi_sysfs_initialize().  We have
	 * remoed sysfs visibility from the device, so make the target
	 * invisible if this was the last device underneath it.
	 */
	scsi_target_reap(scsi_target(sdev));

	put_device(dev);
}
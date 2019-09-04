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
struct dasd_device {int /*<<< orphan*/  flags; struct dasd_block* block; } ;
struct dasd_block {scalar_t__ bdev; int /*<<< orphan*/  open_count; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FLAG_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE ; 
 int /*<<< orphan*/  DASD_FLAG_SAFE_OFFLINE_RUNNING ; 
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 int PTR_ERR (struct dasd_device*) ; 
 int /*<<< orphan*/  _wait_for_empty_queues (struct dasd_device*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_delete_device (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev_locked (struct ccw_device*) ; 
 int /*<<< orphan*/  dasd_free_block (struct dasd_block*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_set_target_state (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int fsync_bdev (scalar_t__) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown_waitq ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dasd_generic_set_offline(struct ccw_device *cdev)
{
	struct dasd_device *device;
	struct dasd_block *block;
	int max_count, open_count, rc;
	unsigned long flags;

	rc = 0;
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	device = dasd_device_from_cdev_locked(cdev);
	if (IS_ERR(device)) {
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		return PTR_ERR(device);
	}

	/*
	 * We must make sure that this device is currently not in use.
	 * The open_count is increased for every opener, that includes
	 * the blkdev_get in dasd_scan_partitions. We are only interested
	 * in the other openers.
	 */
	if (device->block) {
		max_count = device->block->bdev ? 0 : -1;
		open_count = atomic_read(&device->block->open_count);
		if (open_count > max_count) {
			if (open_count > 0)
				pr_warn("%s: The DASD cannot be set offline with open count %i\n",
					dev_name(&cdev->dev), open_count);
			else
				pr_warn("%s: The DASD cannot be set offline while it is in use\n",
					dev_name(&cdev->dev));
			rc = -EBUSY;
			goto out_err;
		}
	}

	/*
	 * Test if the offline processing is already running and exit if so.
	 * If a safe offline is being processed this could only be a normal
	 * offline that should be able to overtake the safe offline and
	 * cancel any I/O we do not want to wait for any longer
	 */
	if (test_bit(DASD_FLAG_OFFLINE, &device->flags)) {
		if (test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
			clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING,
				  &device->flags);
		} else {
			rc = -EBUSY;
			goto out_err;
		}
	}
	set_bit(DASD_FLAG_OFFLINE, &device->flags);

	/*
	 * if safe_offline is called set safe_offline_running flag and
	 * clear safe_offline so that a call to normal offline
	 * can overrun safe_offline processing
	 */
	if (test_and_clear_bit(DASD_FLAG_SAFE_OFFLINE, &device->flags) &&
	    !test_and_set_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
		/* need to unlock here to wait for outstanding I/O */
		spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
		/*
		 * If we want to set the device safe offline all IO operations
		 * should be finished before continuing the offline process
		 * so sync bdev first and then wait for our queues to become
		 * empty
		 */
		if (device->block) {
			rc = fsync_bdev(device->block->bdev);
			if (rc != 0)
				goto interrupted;
		}
		dasd_schedule_device_bh(device);
		rc = wait_event_interruptible(shutdown_waitq,
					      _wait_for_empty_queues(device));
		if (rc != 0)
			goto interrupted;

		/*
		 * check if a normal offline process overtook the offline
		 * processing in this case simply do nothing beside returning
		 * that we got interrupted
		 * otherwise mark safe offline as not running any longer and
		 * continue with normal offline
		 */
		spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
		if (!test_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags)) {
			rc = -ERESTARTSYS;
			goto out_err;
		}
		clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags);
	}
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);

	dasd_set_target_state(device, DASD_STATE_NEW);
	/* dasd_delete_device destroys the device reference. */
	block = device->block;
	dasd_delete_device(device);
	/*
	 * life cycle of block is bound to device, so delete it after
	 * device was safely removed
	 */
	if (block)
		dasd_free_block(block);

	return 0;

interrupted:
	/* interrupted by signal */
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	clear_bit(DASD_FLAG_SAFE_OFFLINE_RUNNING, &device->flags);
	clear_bit(DASD_FLAG_OFFLINE, &device->flags);
out_err:
	dasd_put_device(device);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	return rc;
}
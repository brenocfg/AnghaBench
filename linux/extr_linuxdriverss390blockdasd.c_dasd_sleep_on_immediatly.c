#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  next; } ;
struct dasd_device {scalar_t__ block; int /*<<< orphan*/  cdev; TYPE_1__ ccw_queue; int /*<<< orphan*/  flags; } ;
struct dasd_ccw_req {scalar_t__ status; int intrc; int /*<<< orphan*/  devlist; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  flags; struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_ALLOW_SLOCK ; 
 scalar_t__ DASD_CQR_DONE ; 
 scalar_t__ DASD_CQR_FAILED ; 
 scalar_t__ DASD_CQR_QUEUED ; 
 int /*<<< orphan*/  DASD_FLAG_LOCK_STOLEN ; 
 int /*<<< orphan*/  DASD_SLEEPON_START_TAG ; 
 int EIO ; 
 int EPERM ; 
 int _dasd_term_running_cqr (struct dasd_device*) ; 
 int /*<<< orphan*/  _wait_for_wakeup (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (scalar_t__) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_wakeup_cb ; 
 int /*<<< orphan*/  generic_waitq ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dasd_sleep_on_immediatly(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device;
	int rc;

	device = cqr->startdev;
	if (test_bit(DASD_FLAG_LOCK_STOLEN, &device->flags) &&
	    !test_bit(DASD_CQR_ALLOW_SLOCK, &cqr->flags)) {
		cqr->status = DASD_CQR_FAILED;
		cqr->intrc = -EPERM;
		return -EIO;
	}
	spin_lock_irq(get_ccwdev_lock(device->cdev));
	rc = _dasd_term_running_cqr(device);
	if (rc) {
		spin_unlock_irq(get_ccwdev_lock(device->cdev));
		return rc;
	}
	cqr->callback = dasd_wakeup_cb;
	cqr->callback_data = DASD_SLEEPON_START_TAG;
	cqr->status = DASD_CQR_QUEUED;
	/*
	 * add new request as second
	 * first the terminated cqr needs to be finished
	 */
	list_add(&cqr->devlist, device->ccw_queue.next);

	/* let the bh start the request to keep them in order */
	dasd_schedule_device_bh(device);

	spin_unlock_irq(get_ccwdev_lock(device->cdev));

	wait_event(generic_waitq, _wait_for_wakeup(cqr));

	if (cqr->status == DASD_CQR_DONE)
		rc = 0;
	else if (cqr->intrc)
		rc = cqr->intrc;
	else
		rc = -EIO;

	/* kick tasklets */
	dasd_schedule_device_bh(device);
	if (device->block)
		dasd_schedule_block_bh(device->block);

	return rc;
}
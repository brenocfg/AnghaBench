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
struct dasd_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  ccw_queue; } ;
struct dasd_ccw_req {int /*<<< orphan*/  devlist; int /*<<< orphan*/  status; struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_QUEUED ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

void dasd_add_request_head(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device;
	unsigned long flags;

	device = cqr->startdev;
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	cqr->status = DASD_CQR_QUEUED;
	list_add(&cqr->devlist, &device->ccw_queue);
	/* let the bh start the request to keep them in order */
	dasd_schedule_device_bh(device);
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
}
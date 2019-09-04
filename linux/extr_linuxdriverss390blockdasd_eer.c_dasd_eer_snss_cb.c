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
struct dasd_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; struct dasd_ccw_req* eer_cqr; } ;
struct dasd_ccw_req {struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_EER_STATECHANGE ; 
 int /*<<< orphan*/  DASD_FLAG_EER_IN_USE ; 
 int /*<<< orphan*/  DASD_FLAG_EER_SNSS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_eer_snss (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_eer_write (struct dasd_device*,struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,struct dasd_device*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eer_snss_cb(struct dasd_ccw_req *cqr, void *data)
{
	struct dasd_device *device = cqr->startdev;
	unsigned long flags;

	dasd_eer_write(device, cqr, DASD_EER_STATECHANGE);
	spin_lock_irqsave(get_ccwdev_lock(device->cdev), flags);
	if (device->eer_cqr == cqr) {
		clear_bit(DASD_FLAG_EER_IN_USE, &device->flags);
		if (test_bit(DASD_FLAG_EER_SNSS, &device->flags))
			/* Another SNSS has been requested in the meantime. */
			dasd_eer_snss(device);
		cqr = NULL;
	}
	spin_unlock_irqrestore(get_ccwdev_lock(device->cdev), flags);
	if (cqr)
		/*
		 * Extended error recovery has been switched off while
		 * the SNSS request was running. It could even have
		 * been switched off and on again in which case there
		 * is a new ccw in device->eer_cqr. Free the "old"
		 * snss request now.
		 */
		dasd_sfree_request(cqr, device);
}
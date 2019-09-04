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
struct request {int dummy; } ;
struct dasd_eckd_private {int /*<<< orphan*/  count; } ;
struct dasd_ccw_req {TYPE_1__* memdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; struct dasd_eckd_private* private; } ;

/* Variables and functions */
 int dasd_eckd_free_cp (struct dasd_ccw_req*,struct request*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dasd_eckd_free_alias_cp(struct dasd_ccw_req *cqr,
				   struct request *req)
{
	struct dasd_eckd_private *private;
	unsigned long flags;

	spin_lock_irqsave(get_ccwdev_lock(cqr->memdev->cdev), flags);
	private = cqr->memdev->private;
	private->count--;
	spin_unlock_irqrestore(get_ccwdev_lock(cqr->memdev->cdev), flags);
	return dasd_eckd_free_cp(cqr, req);
}
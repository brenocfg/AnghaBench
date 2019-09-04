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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_ccw_req {scalar_t__ function; int retries; struct dasd_device* startdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  dasd_3990_erp_block_queue (struct dasd_ccw_req*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_int_req(struct dasd_ccw_req * erp)
{

	struct dasd_device *device = erp->startdev;

	/* first time set initial retry counter and erp_function */
	/* and retry once without blocking queue		 */
	/* (this enables easier enqueing of the cqr)		 */
	if (erp->function != dasd_3990_erp_int_req) {

		erp->retries = 256;
		erp->function = dasd_3990_erp_int_req;

	} else {

		/* issue a message and wait for 'device ready' interrupt */
		dev_err(&device->cdev->dev,
			    "is offline or not installed - "
			    "INTERVENTION REQUIRED!!\n");

		dasd_3990_erp_block_queue(erp, 60*HZ);
	}

	return erp;

}
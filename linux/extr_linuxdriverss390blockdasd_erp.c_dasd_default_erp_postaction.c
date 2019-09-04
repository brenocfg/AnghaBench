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
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {scalar_t__ status; unsigned long startclk; unsigned long stopclk; struct dasd_device* startdev; int /*<<< orphan*/  memdev; int /*<<< orphan*/  blocklist; struct dasd_ccw_req* refers; int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DASD_CQR_DONE ; 
 scalar_t__ DASD_CQR_FAILED ; 
 int /*<<< orphan*/  dasd_free_erp_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 unsigned long get_tod_clock () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

struct dasd_ccw_req *dasd_default_erp_postaction(struct dasd_ccw_req *cqr)
{
	int success;
	unsigned long startclk, stopclk;
	struct dasd_device *startdev;

	BUG_ON(cqr->refers == NULL || cqr->function == NULL);

	success = cqr->status == DASD_CQR_DONE;
	startclk = cqr->startclk;
	stopclk = cqr->stopclk;
	startdev = cqr->startdev;

	/* free all ERPs - but NOT the original cqr */
	while (cqr->refers != NULL) {
		struct dasd_ccw_req *refers;

		refers = cqr->refers;
		/* remove the request from the block queue */
		list_del(&cqr->blocklist);
		/* free the finished erp request */
		dasd_free_erp_request(cqr, cqr->memdev);
		cqr = refers;
	}

	/* set corresponding status to original cqr */
	cqr->startclk = startclk;
	cqr->stopclk = stopclk;
	cqr->startdev = startdev;
	if (success)
		cqr->status = DASD_CQR_DONE;
	else {
		cqr->status = DASD_CQR_FAILED;
		cqr->stopclk = get_tod_clock();
	}

	return cqr;

}
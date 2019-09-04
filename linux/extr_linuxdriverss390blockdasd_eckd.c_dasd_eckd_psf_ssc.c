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
struct dasd_ccw_req {unsigned long flags; int intrc; int /*<<< orphan*/  memdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 int PTR_ERR (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  css_schedule_reprobe () ; 
 struct dasd_ccw_req* dasd_eckd_build_psf_ssc (struct dasd_device*,int) ; 
 int /*<<< orphan*/  dasd_sfree_request (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 
 int dasd_sleep_on (struct dasd_ccw_req*) ; 

__attribute__((used)) static int
dasd_eckd_psf_ssc(struct dasd_device *device, int enable_pav,
		  unsigned long flags)
{
	struct dasd_ccw_req *cqr;
	int rc;

	cqr = dasd_eckd_build_psf_ssc(device, enable_pav);
	if (IS_ERR(cqr))
		return PTR_ERR(cqr);

	/*
	 * set flags e.g. turn on failfast, to prevent blocking
	 * the calling function should handle failed requests
	 */
	cqr->flags |= flags;

	rc = dasd_sleep_on(cqr);
	if (!rc)
		/* trigger CIO to reprobe devices */
		css_schedule_reprobe();
	else if (cqr->intrc == -EAGAIN)
		rc = -EAGAIN;

	dasd_sfree_request(cqr, cqr->memdev);
	return rc;
}
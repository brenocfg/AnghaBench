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
struct dasd_ccw_req {scalar_t__ status; scalar_t__ refers; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_DONE ; 
 scalar_t__ DASD_CQR_FAILED ; 
 scalar_t__ DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_FLAGS_USE_ERP ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dasd_sleep_on_loop_condition(struct dasd_ccw_req *cqr)
{
	if (test_bit(DASD_CQR_FLAGS_USE_ERP, &cqr->flags)) {
		if (cqr->refers) /* erp is not done yet */
			return 1;
		return ((cqr->status != DASD_CQR_DONE) &&
			(cqr->status != DASD_CQR_FAILED));
	} else
		return (cqr->status == DASD_CQR_FILLED);
}
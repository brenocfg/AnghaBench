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
struct dasd_ccw_req {int retries; struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*) ;} ;

/* Variables and functions */

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_action_5(struct dasd_ccw_req * erp)
{

	/* first of all retry */
	erp->retries = 10;
	erp->function = dasd_3990_erp_action_5;

	return erp;

}
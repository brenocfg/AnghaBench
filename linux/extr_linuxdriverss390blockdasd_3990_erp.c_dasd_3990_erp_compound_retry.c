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
struct dasd_ccw_req {int retries; void (* function ) (struct dasd_ccw_req*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static void
dasd_3990_erp_compound_retry(struct dasd_ccw_req * erp, char *sense)
{

	switch (sense[25] & 0x03) {
	case 0x00:		/* no not retry */
		erp->retries = 1;
		break;

	case 0x01:		/* retry 2 times */
		erp->retries = 2;
		break;

	case 0x02:		/* retry 10 times */
		erp->retries = 10;
		break;

	case 0x03:		/* retry 256 times */
		erp->retries = 256;
		break;

	default:
		BUG();
	}

	erp->function = dasd_3990_erp_compound_retry;

}
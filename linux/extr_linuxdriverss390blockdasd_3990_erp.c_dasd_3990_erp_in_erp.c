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
struct dasd_ccw_req {struct dasd_ccw_req* refers; } ;

/* Variables and functions */
 int dasd_3990_erp_error_match (struct dasd_ccw_req*,struct dasd_ccw_req*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_in_erp(struct dasd_ccw_req *cqr)
{

	struct dasd_ccw_req *erp_head = cqr,	/* save erp chain head */
	*erp_match = NULL;	/* save erp chain head */
	int match = 0;		/* 'boolean' for matching error found */

	if (cqr->refers == NULL) {	/* return if not in erp */
		return NULL;
	}

	/* check the erp/cqr chain for current error */
	do {
		match = dasd_3990_erp_error_match(erp_head, cqr->refers);
		erp_match = cqr;	/* save possible matching erp  */
		cqr = cqr->refers;	/* check next erp/cqr in queue */

	} while ((cqr->refers != NULL) && (!match));

	if (!match) {
		return NULL;	/* no match was found */
	}

	return erp_match;	/* return address of matching erp */

}
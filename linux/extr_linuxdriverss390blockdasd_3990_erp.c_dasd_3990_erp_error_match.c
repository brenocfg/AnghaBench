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
struct TYPE_2__ {int /*<<< orphan*/  scsw; } ;
struct dasd_ccw_req {scalar_t__ startdev; TYPE_1__ irb; } ;

/* Variables and functions */
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 char* dasd_get_sense (TYPE_1__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_3990_erp_error_match(struct dasd_ccw_req *cqr1,
				     struct dasd_ccw_req *cqr2)
{
	char *sense1, *sense2;

	if (cqr1->startdev != cqr2->startdev)
		return 0;

	sense1 = dasd_get_sense(&cqr1->irb);
	sense2 = dasd_get_sense(&cqr2->irb);

	/* one request has sense data, the other not -> no match, return 0 */
	if (!sense1 != !sense2)
		return 0;
	/* no sense data in both cases -> check cstat for IFCC */
	if (!sense1 && !sense2)	{
		if ((scsw_cstat(&cqr1->irb.scsw) & (SCHN_STAT_INTF_CTRL_CHK |
						    SCHN_STAT_CHN_CTRL_CHK)) ==
		    (scsw_cstat(&cqr2->irb.scsw) & (SCHN_STAT_INTF_CTRL_CHK |
						    SCHN_STAT_CHN_CTRL_CHK)))
			return 1; /* match with ifcc*/
	}
	/* check sense data; byte 0-2,25,27 */
	if (!(sense1 && sense2 &&
	      (memcmp(sense1, sense2, 3) == 0) &&
	      (sense1[27] == sense2[27]) &&
	      (sense1[25] == sense2[25]))) {

		return 0;	/* sense doesn't match */
	}

	return 1;		/* match */

}
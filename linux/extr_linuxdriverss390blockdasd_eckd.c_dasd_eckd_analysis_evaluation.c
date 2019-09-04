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
struct dasd_ccw_req {scalar_t__ status; int /*<<< orphan*/  irb; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_DONE ; 
 scalar_t__ DASD_CQR_FAILED ; 
 scalar_t__ DASD_CQR_NEED_ERP ; 
 int INIT_CQR_ERROR ; 
 int INIT_CQR_OK ; 
 int INIT_CQR_UNFORMATTED ; 
 char SNS1_NO_REC_FOUND ; 
 char* dasd_get_sense (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_eckd_analysis_evaluation(struct dasd_ccw_req *init_cqr)
{
	char *sense;
	if (init_cqr->status == DASD_CQR_DONE)
		return INIT_CQR_OK;
	else if (init_cqr->status == DASD_CQR_NEED_ERP ||
		 init_cqr->status == DASD_CQR_FAILED) {
		sense = dasd_get_sense(&init_cqr->irb);
		if (sense && (sense[1] & SNS1_NO_REC_FOUND))
			return INIT_CQR_UNFORMATTED;
		else
			return INIT_CQR_ERROR;
	} else
		return INIT_CQR_ERROR;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {TYPE_3__* cdev; } ;
struct TYPE_5__ {scalar_t__ cpa; } ;
struct TYPE_8__ {TYPE_1__ cmd; } ;
struct TYPE_6__ {TYPE_4__ scsw; } ;
struct dasd_ccw_req {char* data; void* status; struct ccw1* cpaddr; TYPE_2__ irb; struct dasd_ccw_req* refers; struct dasd_device* startdev; } ;
struct ccw1 {scalar_t__ cda; } ;
struct DE_eckd_data {int dummy; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DASD_CQR_FAILED ; 
 void* DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ scsw_is_tm (TYPE_4__*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_update_1B(struct dasd_ccw_req * previous_erp, char *sense)
{

	struct dasd_device *device = previous_erp->startdev;
	__u32 cpa = 0;
	struct dasd_ccw_req *cqr;
	struct dasd_ccw_req *erp;
	char *LO_data;		/* struct LO_eckd_data */
	struct ccw1 *ccw;

	DBF_DEV_EVENT(DBF_WARNING, device, "%s",
		    "Write not finished because of unexpected condition"
		    " - follow on");

	/* determine the original cqr */
	cqr = previous_erp;

	while (cqr->refers != NULL) {
		cqr = cqr->refers;
	}

	if (scsw_is_tm(&cqr->irb.scsw)) {
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			      "32 bit sense, action 1B, update,"
			      " in transport mode - just retry");
		return previous_erp;
	}

	/* for imprecise ending just do default erp */
	if (sense[1] & 0x01) {
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "Imprecise ending is set - just retry");

		previous_erp->status = DASD_CQR_FILLED;

		return previous_erp;
	}

	/* determine the address of the CCW to be restarted */
	/* Imprecise ending is not set -> addr from IRB-SCSW */
	cpa = previous_erp->irb.scsw.cmd.cpa;

	if (cpa == 0) {
		/* internal error 02 -
		   Unable to determine address of the CCW to be restarted */
		dev_err(&device->cdev->dev, "An error occurred in the DASD "
			"device driver, reason=%s\n", "02");

		previous_erp->status = DASD_CQR_FAILED;

		return previous_erp;
	}

	erp = previous_erp;

	/* update the LO with the new returned sense data  */
	LO_data = erp->data + sizeof(struct DE_eckd_data);

	if ((sense[3] == 0x01) && (LO_data[1] & 0x01)) {
		/* should not happen */
		previous_erp->status = DASD_CQR_FAILED;

		return previous_erp;
	}

	if ((sense[7] & 0x3F) == 0x01) {
		/* operation code is WRITE DATA -> data area orientation */
		LO_data[0] = 0x81;

	} else if ((sense[7] & 0x3F) == 0x03) {
		/* operation code is FORMAT WRITE -> index orientation */
		LO_data[0] = 0xC3;

	} else {
		LO_data[0] = sense[7];	/* operation */
	}

	LO_data[1] = sense[8];	/* auxiliary */
	LO_data[2] = sense[9];
	LO_data[3] = sense[3];	/* count */
	LO_data[4] = sense[29];	/* seek_addr.cyl */
	LO_data[5] = sense[30];	/* seek_addr.cyl 2nd byte */
	LO_data[7] = sense[31];	/* seek_addr.head 2nd byte */

	memcpy(&(LO_data[8]), &(sense[11]), 8);

	/* TIC to the failed ccw */
	ccw = erp->cpaddr;	/* addr of DE ccw */
	ccw++;			/* addr of LE ccw */
	ccw++;			/* addr of TIC ccw */
	ccw->cda = cpa;

	erp->status = DASD_CQR_FILLED;

	return erp;

}
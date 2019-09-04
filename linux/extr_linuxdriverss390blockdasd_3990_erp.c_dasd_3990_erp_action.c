#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dasd_device {int features; TYPE_2__* cdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  scsw; } ;
struct dasd_ccw_req {int /*<<< orphan*/  blocklist; int /*<<< orphan*/  status; struct dasd_ccw_req* refers; scalar_t__ lpm; int /*<<< orphan*/  flags; TYPE_1__ irb; struct dasd_device* startdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_DONE ; 
 int /*<<< orphan*/  DASD_CQR_IN_ERP ; 
 int /*<<< orphan*/  DASD_CQR_VERIFY_PATH ; 
 int DASD_FEATURE_ERPLOG ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,struct dasd_ccw_req*) ; 
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_DEV_END ; 
 scalar_t__ IS_ERR (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_additional_erp (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_handle_match_erp (struct dasd_ccw_req*,struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_in_erp (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int scsw_cstat (int /*<<< orphan*/ *) ; 
 int scsw_dstat (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct dasd_ccw_req *
dasd_3990_erp_action(struct dasd_ccw_req * cqr)
{
	struct dasd_ccw_req *erp = NULL;
	struct dasd_device *device = cqr->startdev;
	struct dasd_ccw_req *temp_erp = NULL;

	if (device->features & DASD_FEATURE_ERPLOG) {
		/* print current erp_chain */
		dev_err(&device->cdev->dev,
			    "ERP chain at BEGINNING of ERP-ACTION\n");
		for (temp_erp = cqr;
		     temp_erp != NULL; temp_erp = temp_erp->refers) {

			dev_err(&device->cdev->dev,
				    "ERP %p (%02x) refers to %p\n",
				    temp_erp, temp_erp->status,
				    temp_erp->refers);
		}
	}

	/* double-check if current erp/cqr was successful */
	if ((scsw_cstat(&cqr->irb.scsw) == 0x00) &&
	    (scsw_dstat(&cqr->irb.scsw) ==
	     (DEV_STAT_CHN_END | DEV_STAT_DEV_END))) {

		DBF_DEV_EVENT(DBF_DEBUG, device,
			    "ERP called for successful request %p"
			    " - NO ERP necessary", cqr);

		cqr->status = DASD_CQR_DONE;

		return cqr;
	}

	/* check if error happened before */
	erp = dasd_3990_erp_in_erp(cqr);

	if (erp == NULL) {
		/* no matching erp found - set up erp */
		erp = dasd_3990_erp_additional_erp(cqr);
		if (IS_ERR(erp))
			return erp;
	} else {
		/* matching erp found - set all leading erp's to DONE */
		erp = dasd_3990_erp_handle_match_erp(cqr, erp);
	}


	/*
	 * For path verification work we need to stick with the path that was
	 * originally chosen so that the per path configuration data is
	 * assigned correctly.
	 */
	if (test_bit(DASD_CQR_VERIFY_PATH, &erp->flags) && cqr->lpm) {
		erp->lpm = cqr->lpm;
	}

	if (device->features & DASD_FEATURE_ERPLOG) {
		/* print current erp_chain */
		dev_err(&device->cdev->dev,
			    "ERP chain at END of ERP-ACTION\n");
		for (temp_erp = erp;
		     temp_erp != NULL; temp_erp = temp_erp->refers) {

			dev_err(&device->cdev->dev,
				    "ERP %p (%02x) refers to %p\n",
				    temp_erp, temp_erp->status,
				    temp_erp->refers);
		}
	}

	/* enqueue ERP request if it's a new one */
	if (list_empty(&erp->blocklist)) {
		cqr->status = DASD_CQR_IN_ERP;
		/* add erp request before the cqr */
		list_add_tail(&erp->blocklist, &cqr->blocklist);
	}



	return erp;

}
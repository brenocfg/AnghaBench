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
struct dasd_device {TYPE_1__* cdev; } ;
struct dasd_ccw_req {int status; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct dasd_ccw_req*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DASD_CQR_CLEARED 130 
 int DASD_CQR_DONE ; 
#define  DASD_CQR_ERROR 129 
 int DASD_CQR_NEED_ERP ; 
#define  DASD_CQR_SUCCESS 128 
 int DASD_CQR_TERMINATED ; 
 int ERRORLENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,struct dasd_ccw_req*,int) ; 
 int /*<<< orphan*/  stub1 (struct dasd_ccw_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dasd_process_cqr(struct dasd_device *device,
			       struct dasd_ccw_req *cqr)
{
	char errorstring[ERRORLENGTH];

	switch (cqr->status) {
	case DASD_CQR_SUCCESS:
		cqr->status = DASD_CQR_DONE;
		break;
	case DASD_CQR_ERROR:
		cqr->status = DASD_CQR_NEED_ERP;
		break;
	case DASD_CQR_CLEARED:
		cqr->status = DASD_CQR_TERMINATED;
		break;
	default:
		/* internal error 12 - wrong cqr status*/
		snprintf(errorstring, ERRORLENGTH, "12 %p %x02", cqr, cqr->status);
		dev_err(&device->cdev->dev,
			"An error occurred in the DASD device driver, "
			"reason=%s\n", errorstring);
		BUG();
	}
	if (cqr->callback)
		cqr->callback(cqr, cqr->callback_data);
}
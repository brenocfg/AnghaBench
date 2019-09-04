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
typedef  int /*<<< orphan*/  u8 ;
struct us_data {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_2__ {int lun; } ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_ERROR ; 
 int sddr09_transport (struct scsi_cmnd*,struct us_data*) ; 
 int usb_stor_CB_transport (struct scsi_cmnd*,struct us_data*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpcm_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	int ret;

	usb_stor_dbg(us, "LUN=%d\n", (u8)srb->device->lun);

	switch (srb->device->lun) {
	case 0:

		/*
		 * LUN 0 corresponds to the CompactFlash card reader.
		 */
		ret = usb_stor_CB_transport(srb, us);
		break;

	case 1:

		/*
		 * LUN 1 corresponds to the SmartMedia card reader.
		 */

		/*
		 * Set the LUN to 0 (just in case).
		 */
		srb->device->lun = 0;
		ret = sddr09_transport(srb, us);
		srb->device->lun = 1;
		break;

	default:
	    usb_stor_dbg(us, "Invalid LUN %d\n", (u8)srb->device->lun);
		ret = USB_STOR_TRANSPORT_ERROR;
		break;
	}
	return ret;
}
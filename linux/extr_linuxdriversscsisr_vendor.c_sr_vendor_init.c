#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vendor; } ;
typedef  TYPE_1__ Scsi_CD ;

/* Variables and functions */
 int /*<<< orphan*/  VENDOR_SCSI3 ; 

void sr_vendor_init(Scsi_CD *cd)
{
#ifndef CONFIG_BLK_DEV_SR_VENDOR
	cd->vendor = VENDOR_SCSI3;
#else
	const char *vendor = cd->device->vendor;
	const char *model = cd->device->model;
	
	/* default */
	cd->vendor = VENDOR_SCSI3;
	if (cd->readcd_known)
		/* this is true for scsi3/mmc drives - no more checks */
		return;

	if (cd->device->type == TYPE_WORM) {
		cd->vendor = VENDOR_WRITER;

	} else if (!strncmp(vendor, "NEC", 3)) {
		cd->vendor = VENDOR_NEC;
		if (!strncmp(model, "CD-ROM DRIVE:25", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:36", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:83", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:84 ", 16)
#if 0
		/* my NEC 3x returns the read-raw data if a read-raw
		   is followed by a read for the same sector - aeb */
		    || !strncmp(model, "CD-ROM DRIVE:500", 16)
#endif
		    )
			/* these can't handle multisession, may hang */
			cd->cdi.mask |= CDC_MULTI_SESSION;

	} else if (!strncmp(vendor, "TOSHIBA", 7)) {
		cd->vendor = VENDOR_TOSHIBA;

	}
#endif
}
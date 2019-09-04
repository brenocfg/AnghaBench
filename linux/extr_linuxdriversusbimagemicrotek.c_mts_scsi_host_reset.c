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
struct scsi_cmnd {TYPE_2__* device; } ;
struct mts_desc {int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  usb_intf; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 int SUCCESS ; 
 int /*<<< orphan*/  mts_debug_dump (struct mts_desc*) ; 
 int usb_lock_device_for_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_reset_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlock_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mts_scsi_host_reset(struct scsi_cmnd *srb)
{
	struct mts_desc* desc = (struct mts_desc*)(srb->device->host->hostdata[0]);
	int result;

	MTS_DEBUG_GOT_HERE();
	mts_debug_dump(desc);

	result = usb_lock_device_for_reset(desc->usb_dev, desc->usb_intf);
	if (result == 0) {
		result = usb_reset_device(desc->usb_dev);
		usb_unlock_device(desc->usb_dev);
	}
	return result ? FAILED : SUCCESS;
}
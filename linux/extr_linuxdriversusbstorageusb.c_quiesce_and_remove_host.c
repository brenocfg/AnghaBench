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
struct us_data {int /*<<< orphan*/  delay_wait; int /*<<< orphan*/  dflags; int /*<<< orphan*/  pusb_intf; int /*<<< orphan*/  scan_dwork; TYPE_1__* pusb_dev; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  US_FLIDX_DISCONNECTING ; 
 int /*<<< orphan*/  US_FLIDX_SCAN_PENDING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_lock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_unlock (struct Scsi_Host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_no_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quiesce_and_remove_host(struct us_data *us)
{
	struct Scsi_Host *host = us_to_host(us);

	/* If the device is really gone, cut short reset delays */
	if (us->pusb_dev->state == USB_STATE_NOTATTACHED) {
		set_bit(US_FLIDX_DISCONNECTING, &us->dflags);
		wake_up(&us->delay_wait);
	}

	/*
	 * Prevent SCSI scanning (if it hasn't started yet)
	 * or wait for the SCSI-scanning routine to stop.
	 */
	cancel_delayed_work_sync(&us->scan_dwork);

	/* Balance autopm calls if scanning was cancelled */
	if (test_bit(US_FLIDX_SCAN_PENDING, &us->dflags))
		usb_autopm_put_interface_no_suspend(us->pusb_intf);

	/*
	 * Removing the host will perform an orderly shutdown: caches
	 * synchronized, disks spun down, etc.
	 */
	scsi_remove_host(host);

	/*
	 * Prevent any new commands from being accepted and cut short
	 * reset delays.
	 */
	scsi_lock(host);
	set_bit(US_FLIDX_DISCONNECTING, &us->dflags);
	scsi_unlock(host);
	wake_up(&us->delay_wait);
}
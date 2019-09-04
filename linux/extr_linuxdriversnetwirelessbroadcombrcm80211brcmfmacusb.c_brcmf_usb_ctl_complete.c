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
struct TYPE_3__ {int /*<<< orphan*/  tx_ctlerrs; int /*<<< orphan*/  tx_ctlpkts; int /*<<< orphan*/  rx_ctlerrs; int /*<<< orphan*/  rx_ctlpkts; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;
struct brcmf_usbdev_info {int ctl_urb_status; int ctl_completed; TYPE_2__ bus_pub; } ;

/* Variables and functions */
 int BRCMF_USB_CBCTL_READ ; 
 int BRCMF_USB_CBCTL_WRITE ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  brcmf_usb_ioctl_resp_wake (struct brcmf_usbdev_info*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_usb_ctl_complete(struct brcmf_usbdev_info *devinfo, int type, int status)
{
	brcmf_dbg(USB, "Enter, status=%d\n", status);

	if (unlikely(devinfo == NULL))
		return;

	if (type == BRCMF_USB_CBCTL_READ) {
		if (status == 0)
			devinfo->bus_pub.stats.rx_ctlpkts++;
		else
			devinfo->bus_pub.stats.rx_ctlerrs++;
	} else if (type == BRCMF_USB_CBCTL_WRITE) {
		if (status == 0)
			devinfo->bus_pub.stats.tx_ctlpkts++;
		else
			devinfo->bus_pub.stats.tx_ctlerrs++;
	}

	devinfo->ctl_urb_status = status;
	devinfo->ctl_completed = true;
	brcmf_usb_ioctl_resp_wake(devinfo);
}
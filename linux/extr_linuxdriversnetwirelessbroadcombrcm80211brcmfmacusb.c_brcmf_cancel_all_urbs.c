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
struct brcmf_usbdev_info {int /*<<< orphan*/  rx_postq; int /*<<< orphan*/  tx_postq; scalar_t__ bulk_urb; scalar_t__ ctl_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_usb_free_q (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void brcmf_cancel_all_urbs(struct brcmf_usbdev_info *devinfo)
{
	if (devinfo->ctl_urb)
		usb_kill_urb(devinfo->ctl_urb);
	if (devinfo->bulk_urb)
		usb_kill_urb(devinfo->bulk_urb);
	brcmf_usb_free_q(&devinfo->tx_postq, true);
	brcmf_usb_free_q(&devinfo->rx_postq, true);
}
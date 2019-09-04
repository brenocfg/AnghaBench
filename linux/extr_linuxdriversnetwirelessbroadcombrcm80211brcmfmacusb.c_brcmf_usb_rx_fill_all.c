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
struct brcmf_usbreq {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct brcmf_usbdev_info {int /*<<< orphan*/  rx_freeq; TYPE_1__ bus_pub; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_USB_STATE_UP ; 
 int /*<<< orphan*/  brcmf_err (char*,scalar_t__) ; 
 struct brcmf_usbreq* brcmf_usb_deq (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_usb_rx_refill (struct brcmf_usbdev_info*,struct brcmf_usbreq*) ; 

__attribute__((used)) static void brcmf_usb_rx_fill_all(struct brcmf_usbdev_info *devinfo)
{
	struct brcmf_usbreq *req;

	if (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP) {
		brcmf_err("bus is not up=%d\n", devinfo->bus_pub.state);
		return;
	}
	while ((req = brcmf_usb_deq(devinfo, &devinfo->rx_freeq, NULL)) != NULL)
		brcmf_usb_rx_refill(devinfo, req);
}
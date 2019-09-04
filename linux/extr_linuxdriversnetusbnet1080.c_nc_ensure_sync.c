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
struct usbnet {int frame_errors; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_USBCTL ; 
 int /*<<< orphan*/  REQUEST_REGISTER ; 
 int USBCTL_FLUSH_OTHER ; 
 int USBCTL_FLUSH_THIS ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rx_err ; 
 scalar_t__ usbnet_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nc_ensure_sync(struct usbnet *dev)
{
	if (++dev->frame_errors <= 5)
		return;

	if (usbnet_write_cmd_async(dev, REQUEST_REGISTER,
					USB_DIR_OUT | USB_TYPE_VENDOR |
					USB_RECIP_DEVICE,
					USBCTL_FLUSH_THIS |
					USBCTL_FLUSH_OTHER,
					REG_USBCTL, NULL, 0))
		return;

	netif_dbg(dev, rx_err, dev->net,
		  "flush net1080; too many framing errors\n");
	dev->frame_errors = 0;
}
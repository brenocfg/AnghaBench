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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct brcmf_usbdev_info {int ctl_completed; int /*<<< orphan*/  ctl_op; TYPE_1__ bus_pub; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_USB_STATE_UP ; 
 int EIO ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 struct brcmf_usbdev_info* brcmf_usb_get_businfo (struct device*) ; 
 int brcmf_usb_ioctl_resp_wait (struct brcmf_usbdev_info*) ; 
 int brcmf_usb_send_ctl (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_usb_tx_ctlpkt(struct device *dev, u8 *buf, u32 len)
{
	int err = 0;
	int timeout = 0;
	struct brcmf_usbdev_info *devinfo = brcmf_usb_get_businfo(dev);

	brcmf_dbg(USB, "Enter\n");
	if (devinfo->bus_pub.state != BRCMFMAC_USB_STATE_UP)
		return -EIO;

	if (test_and_set_bit(0, &devinfo->ctl_op))
		return -EIO;

	devinfo->ctl_completed = false;
	err = brcmf_usb_send_ctl(devinfo, buf, len);
	if (err) {
		brcmf_err("fail %d bytes: %d\n", err, len);
		clear_bit(0, &devinfo->ctl_op);
		return err;
	}
	timeout = brcmf_usb_ioctl_resp_wait(devinfo);
	clear_bit(0, &devinfo->ctl_op);
	if (!timeout) {
		brcmf_err("Txctl wait timed out\n");
		err = -EIO;
	}
	return err;
}
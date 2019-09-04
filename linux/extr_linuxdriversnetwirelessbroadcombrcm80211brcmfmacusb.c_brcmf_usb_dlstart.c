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
struct TYPE_2__ {int devid; int /*<<< orphan*/  state; } ;
struct brcmf_usbdev_info {TYPE_1__ bus_pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMFMAC_USB_STATE_DL_DONE ; 
 int /*<<< orphan*/  BRCMFMAC_USB_STATE_DL_FAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int brcmf_usb_dl_writeimage (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int brcmf_usb_dlstart(struct brcmf_usbdev_info *devinfo, u8 *fw, int len)
{
	int err;

	brcmf_dbg(USB, "Enter\n");

	if (devinfo == NULL)
		return -EINVAL;

	if (devinfo->bus_pub.devid == 0xDEAD)
		return -EINVAL;

	err = brcmf_usb_dl_writeimage(devinfo, fw, len);
	if (err == 0)
		devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DL_DONE;
	else
		devinfo->bus_pub.state = BRCMFMAC_USB_STATE_DL_FAIL;
	brcmf_dbg(USB, "Exit, err=%d\n", err);

	return err;
}
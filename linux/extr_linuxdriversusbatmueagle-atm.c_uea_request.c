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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct uea_softc {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_TIMEOUT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
 int /*<<< orphan*/  UCDC_SEND_ENCAPSULATED_COMMAND ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_request(struct uea_softc *sc,
		u16 value, u16 index, u16 size, const void *data)
{
	u8 *xfer_buff;
	int ret = -ENOMEM;

	xfer_buff = kmemdup(data, size, GFP_KERNEL);
	if (!xfer_buff) {
		uea_err(INS_TO_USBDEV(sc), "can't allocate xfer_buff\n");
		return ret;
	}

	ret = usb_control_msg(sc->usb_dev, usb_sndctrlpipe(sc->usb_dev, 0),
			      UCDC_SEND_ENCAPSULATED_COMMAND,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			      value, index, xfer_buff, size, CTRL_TIMEOUT);

	kfree(xfer_buff);
	if (ret < 0) {
		uea_err(INS_TO_USBDEV(sc), "usb_control_msg error %d\n", ret);
		return ret;
	}

	if (ret != size) {
		uea_err(INS_TO_USBDEV(sc),
		       "usb_control_msg send only %d bytes (instead of %d)\n",
		       ret, size);
		return -EIO;
	}

	return 0;
}
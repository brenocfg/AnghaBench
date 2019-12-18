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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_audio {struct usb_device* dev; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int UAC2_CS_CONTROL_SAM_FREQ ; 
 int /*<<< orphan*/  UAC2_CS_CUR ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sample_rate_v2v3(struct snd_usb_audio *chip, int iface,
			      int altsetting, int clock)
{
	struct usb_device *dev = chip->dev;
	__le32 data;
	int err;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC2_CS_CUR,
			      USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			      UAC2_CS_CONTROL_SAM_FREQ << 8,
			      snd_usb_ctrl_intf(chip) | (clock << 8),
			      &data, sizeof(data));
	if (err < 0) {
		dev_warn(&dev->dev, "%d:%d: cannot get freq (v2/v3): err %d\n",
			 iface, altsetting, err);
		return 0;
	}

	return le32_to_cpu(data);
}
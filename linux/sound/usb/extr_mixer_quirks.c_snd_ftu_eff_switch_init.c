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
struct usb_mixer_interface {TYPE_1__* chip; } ;
struct usb_device {int dummy; } ;
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_GET_CUR ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned char*,int) ; 
 unsigned int snd_usb_ctrl_intf (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ftu_eff_switch_init(struct usb_mixer_interface *mixer,
				   struct snd_kcontrol *kctl)
{
	struct usb_device *dev = mixer->chip->dev;
	unsigned int pval = kctl->private_value;
	int err;
	unsigned char value[2];

	value[0] = 0x00;
	value[1] = 0x00;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC_GET_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
			      pval & 0xff00,
			      snd_usb_ctrl_intf(mixer->chip) | ((pval & 0xff) << 8),
			      value, 2);
	if (err < 0)
		return err;

	kctl->private_value |= (unsigned int)value[0] << 24;
	return 0;
}
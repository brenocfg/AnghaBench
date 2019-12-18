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
struct usb_host_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct snd_usb_audio {struct usb_device* dev; } ;
struct audioformat {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {unsigned int bEndpointAddress; } ;
struct TYPE_3__ {int bNumEndpoints; } ;

/* Variables and functions */
 int EINVAL ; 
 int UAC_EP_CS_ATTR_PITCH_CONTROL ; 
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_CLASS ; 
 TYPE_2__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_iface_desc (struct usb_host_interface*) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int,unsigned char*,int) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_pitch_v1(struct snd_usb_audio *chip, int iface,
			 struct usb_host_interface *alts,
			 struct audioformat *fmt)
{
	struct usb_device *dev = chip->dev;
	unsigned int ep;
	unsigned char data[1];
	int err;

	if (get_iface_desc(alts)->bNumEndpoints < 1)
		return -EINVAL;
	ep = get_endpoint(alts, 0)->bEndpointAddress;

	data[0] = 1;
	err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
			      USB_TYPE_CLASS|USB_RECIP_ENDPOINT|USB_DIR_OUT,
			      UAC_EP_CS_ATTR_PITCH_CONTROL << 8, ep,
			      data, sizeof(data));
	if (err < 0) {
		usb_audio_err(chip, "%d:%d: cannot set enable PITCH\n",
			      iface, ep);
		return err;
	}

	return 0;
}
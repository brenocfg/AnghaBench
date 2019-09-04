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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_audio {int sample_rate_read_error; struct usb_device* dev; } ;
struct audioformat {int attributes; int /*<<< orphan*/  altsetting; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {unsigned int bEndpointAddress; } ;
struct TYPE_3__ {int bNumEndpoints; } ;

/* Variables and functions */
 int EINVAL ; 
 int UAC_EP_CS_ATTR_SAMPLE_RATE ; 
 int /*<<< orphan*/  UAC_GET_CUR ; 
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 TYPE_2__* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_iface_desc (struct usb_host_interface*) ; 
 int snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned int,unsigned char*,int) ; 
 scalar_t__ snd_usb_get_sample_rate_quirk (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_sample_rate_v1(struct snd_usb_audio *chip, int iface,
			      struct usb_host_interface *alts,
			      struct audioformat *fmt, int rate)
{
	struct usb_device *dev = chip->dev;
	unsigned int ep;
	unsigned char data[3];
	int err, crate;

	if (get_iface_desc(alts)->bNumEndpoints < 1)
		return -EINVAL;
	ep = get_endpoint(alts, 0)->bEndpointAddress;

	/* if endpoint doesn't have sampling rate control, bail out */
	if (!(fmt->attributes & UAC_EP_CS_ATTR_SAMPLE_RATE))
		return 0;

	data[0] = rate;
	data[1] = rate >> 8;
	data[2] = rate >> 16;
	err = snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), UAC_SET_CUR,
			      USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_DIR_OUT,
			      UAC_EP_CS_ATTR_SAMPLE_RATE << 8, ep,
			      data, sizeof(data));
	if (err < 0) {
		dev_err(&dev->dev, "%d:%d: cannot set freq %d to ep %#x\n",
			iface, fmt->altsetting, rate, ep);
		return err;
	}

	/* Don't check the sample rate for devices which we know don't
	 * support reading */
	if (snd_usb_get_sample_rate_quirk(chip))
		return 0;
	/* the firmware is likely buggy, don't repeat to fail too many times */
	if (chip->sample_rate_read_error > 2)
		return 0;

	err = snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), UAC_GET_CUR,
			      USB_TYPE_CLASS | USB_RECIP_ENDPOINT | USB_DIR_IN,
			      UAC_EP_CS_ATTR_SAMPLE_RATE << 8, ep,
			      data, sizeof(data));
	if (err < 0) {
		dev_err(&dev->dev, "%d:%d: cannot get freq at ep %#x\n",
			iface, fmt->altsetting, ep);
		chip->sample_rate_read_error++;
		return 0; /* some devices don't support reading */
	}

	crate = data[0] | (data[1] << 8) | (data[2] << 16);
	if (crate != rate) {
		dev_warn(&dev->dev, "current rate %d is different from the runtime rate %d\n", crate, rate);
		// runtime->rate = crate;
	}

	return 0;
}
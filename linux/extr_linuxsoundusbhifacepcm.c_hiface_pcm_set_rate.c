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
typedef  int /*<<< orphan*/  u16 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct pcm_runtime {TYPE_1__* chip; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIFACE_RATE_176400 ; 
 int /*<<< orphan*/  HIFACE_RATE_192000 ; 
 int /*<<< orphan*/  HIFACE_RATE_352800 ; 
 int /*<<< orphan*/  HIFACE_RATE_384000 ; 
 int /*<<< orphan*/  HIFACE_RATE_44100 ; 
 int /*<<< orphan*/  HIFACE_RATE_48000 ; 
 int /*<<< orphan*/  HIFACE_RATE_88200 ; 
 int /*<<< orphan*/  HIFACE_RATE_96000 ; 
 int /*<<< orphan*/  HIFACE_SET_RATE_REQUEST ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hiface_pcm_set_rate(struct pcm_runtime *rt, unsigned int rate)
{
	struct usb_device *device = rt->chip->dev;
	u16 rate_value;
	int ret;

	/* We are already sure that the rate is supported here thanks to
	 * ALSA constraints
	 */
	switch (rate) {
	case 44100:
		rate_value = HIFACE_RATE_44100;
		break;
	case 48000:
		rate_value = HIFACE_RATE_48000;
		break;
	case 88200:
		rate_value = HIFACE_RATE_88200;
		break;
	case 96000:
		rate_value = HIFACE_RATE_96000;
		break;
	case 176400:
		rate_value = HIFACE_RATE_176400;
		break;
	case 192000:
		rate_value = HIFACE_RATE_192000;
		break;
	case 352800:
		rate_value = HIFACE_RATE_352800;
		break;
	case 384000:
		rate_value = HIFACE_RATE_384000;
		break;
	default:
		dev_err(&device->dev, "Unsupported rate %d\n", rate);
		return -EINVAL;
	}

	/*
	 * USBIO: Vendor 0xb0(wValue=0x0043, wIndex=0x0000)
	 * 43 b0 43 00 00 00 00 00
	 * USBIO: Vendor 0xb0(wValue=0x004b, wIndex=0x0000)
	 * 43 b0 4b 00 00 00 00 00
	 * This control message doesn't have any ack from the
	 * other side
	 */
	ret = usb_control_msg(device, usb_sndctrlpipe(device, 0),
			      HIFACE_SET_RATE_REQUEST,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      rate_value, 0, NULL, 0, 100);
	if (ret < 0) {
		dev_err(&device->dev, "Error setting samplerate %d.\n", rate);
		return ret;
	}

	return 0;
}
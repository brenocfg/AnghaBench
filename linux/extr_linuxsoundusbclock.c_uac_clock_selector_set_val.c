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
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pin ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UAC2_CS_CUR ; 
 int UAC2_CX_CLOCK_SELECTOR ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char*,int) ; 
 int snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 int uac_clock_selector_get_val (struct snd_usb_audio*,int) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int,unsigned char,...) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uac_clock_selector_set_val(struct snd_usb_audio *chip, int selector_id,
					unsigned char pin)
{
	int ret;

	ret = snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			      UAC2_CS_CUR,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_OUT,
			      UAC2_CX_CLOCK_SELECTOR << 8,
			      snd_usb_ctrl_intf(chip) | (selector_id << 8),
			      &pin, sizeof(pin));
	if (ret < 0)
		return ret;

	if (ret != sizeof(pin)) {
		usb_audio_err(chip,
			"setting selector (id %d) unexpected length %d\n",
			selector_id, ret);
		return -EINVAL;
	}

	ret = uac_clock_selector_get_val(chip, selector_id);
	if (ret < 0)
		return ret;

	if (ret != pin) {
		usb_audio_err(chip,
			"setting selector (id %d) to %x failed (current: %d)\n",
			selector_id, pin, ret);
		return -EINVAL;
	}

	return ret;
}
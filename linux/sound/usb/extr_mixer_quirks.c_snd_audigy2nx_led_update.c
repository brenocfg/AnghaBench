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
struct usb_mixer_interface {struct snd_usb_audio* chip; } ;
struct snd_usb_audio {scalar_t__ usb_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 scalar_t__ USB_ID (int,int) ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_audigy2nx_led_update(struct usb_mixer_interface *mixer,
				    int value, int index)
{
	struct snd_usb_audio *chip = mixer->chip;
	int err;

	err = snd_usb_lock_shutdown(chip);
	if (err < 0)
		return err;

	if (chip->usb_id == USB_ID(0x041e, 0x3042))
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      !value, 0, NULL, 0);
	/* USB X-Fi S51 Pro */
	if (chip->usb_id == USB_ID(0x041e, 0x30df))
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      !value, 0, NULL, 0);
	else
		err = snd_usb_ctl_msg(chip->dev,
			      usb_sndctrlpipe(chip->dev, 0), 0x24,
			      USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			      value, index + 2, NULL, 0);
	snd_usb_unlock_shutdown(chip);
	return err;
}
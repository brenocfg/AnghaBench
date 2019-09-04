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
typedef  int /*<<< orphan*/  u8 ;
struct usb_mixer_elem_list {TYPE_2__* kctl; TYPE_1__* mixer; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {struct snd_usb_audio* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC_SET_CUR ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_microii_spdif_switch_update(struct usb_mixer_elem_list *list)
{
	struct snd_usb_audio *chip = list->mixer->chip;
	u8 reg = list->kctl->private_value;
	int err;

	err = snd_usb_lock_shutdown(chip);
	if (err < 0)
		return err;

	err = snd_usb_ctl_msg(chip->dev,
			usb_sndctrlpipe(chip->dev, 0),
			UAC_SET_CUR,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			reg,
			9,
			NULL,
			0);

	snd_usb_unlock_shutdown(chip);
	return err;
}
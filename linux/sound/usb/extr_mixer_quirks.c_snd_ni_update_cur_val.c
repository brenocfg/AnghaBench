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
struct usb_mixer_elem_list {TYPE_2__* kctl; TYPE_1__* mixer; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {unsigned int private_value; } ;
struct TYPE_3__ {struct snd_usb_audio* chip; } ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ni_update_cur_val(struct usb_mixer_elem_list *list)
{
	struct snd_usb_audio *chip = list->mixer->chip;
	unsigned int pval = list->kctl->private_value;
	int err;

	err = snd_usb_lock_shutdown(chip);
	if (err < 0)
		return err;
	err = usb_control_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			      (pval >> 16) & 0xff,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT,
			      pval >> 24, pval & 0xffff, NULL, 0, 1000);
	snd_usb_unlock_shutdown(chip);
	return err;
}
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
struct snd_usb_audio {int /*<<< orphan*/  usb_id; } ;

/* Variables and functions */
 int USB_ID_VENDOR (int /*<<< orphan*/ ) ; 
 struct snd_usb_audio* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

void snd_usb_set_interface_quirk(struct usb_device *dev)
{
	struct snd_usb_audio *chip = dev_get_drvdata(&dev->dev);

	if (!chip)
		return;
	/*
	 * "Playback Design" products need a 50ms delay after setting the
	 * USB interface.
	 */
	switch (USB_ID_VENDOR(chip->usb_id)) {
	case 0x23ba: /* Playback Design */
	case 0x0644: /* TEAC Corp. */
		msleep(50);
		break;
	}
}
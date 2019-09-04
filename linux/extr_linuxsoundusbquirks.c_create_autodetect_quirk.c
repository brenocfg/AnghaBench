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
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int create_auto_midi_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*) ; 
 int create_auto_pcm_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*) ; 

__attribute__((used)) static int create_autodetect_quirk(struct snd_usb_audio *chip,
				   struct usb_interface *iface,
				   struct usb_driver *driver)
{
	int err;

	err = create_auto_pcm_quirk(chip, iface, driver);
	if (err == -ENODEV)
		err = create_auto_midi_quirk(chip, iface, driver);
	return err;
}
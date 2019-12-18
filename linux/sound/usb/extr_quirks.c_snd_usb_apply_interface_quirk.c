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
struct snd_usb_audio {scalar_t__ usb_id; } ;

/* Variables and functions */
 scalar_t__ USB_ID (int,int) ; 
 int audiophile_skip_setting_quirk (struct snd_usb_audio*,int,int) ; 
 int fasttrackpro_skip_setting_quirk (struct snd_usb_audio*,int,int) ; 
 int quattro_skip_setting_quirk (struct snd_usb_audio*,int,int) ; 

int snd_usb_apply_interface_quirk(struct snd_usb_audio *chip,
				  int iface,
				  int altno)
{
	/* audiophile usb: skip altsets incompatible with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2003))
		return audiophile_skip_setting_quirk(chip, iface, altno);
	/* quattro usb: skip altsets incompatible with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2001))
		return quattro_skip_setting_quirk(chip, iface, altno);
	/* fasttrackpro usb: skip altsets incompatible with device_setup */
	if (chip->usb_id == USB_ID(0x0763, 0x2012))
		return fasttrackpro_skip_setting_quirk(chip, iface, altno);

	return 0;
}
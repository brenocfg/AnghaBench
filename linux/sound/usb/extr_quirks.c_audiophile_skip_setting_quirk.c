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
struct snd_usb_audio {int setup; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAUDIO_SET ; 
 unsigned int MAUDIO_SET_16B_48K_DI ; 
 unsigned int MAUDIO_SET_16B_48K_NOTDI ; 
 unsigned int MAUDIO_SET_24B_48K_DI ; 
 unsigned int MAUDIO_SET_24B_48K_NOTDI ; 
 int MAUDIO_SET_96K ; 
 int MAUDIO_SET_DTS ; 
 unsigned int MAUDIO_SET_MASK ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audiophile_skip_setting_quirk(struct snd_usb_audio *chip,
					 int iface,
					 int altno)
{
	/* Reset ALL ifaces to 0 altsetting.
	 * Call it for every possible altsetting of every interface.
	 */
	usb_set_interface(chip->dev, iface, 0);

	if (chip->setup & MAUDIO_SET) {
		unsigned int mask;
		if ((chip->setup & MAUDIO_SET_DTS) && altno != 6)
			return 1; /* skip this altsetting */
		if ((chip->setup & MAUDIO_SET_96K) && altno != 1)
			return 1; /* skip this altsetting */
		mask = chip->setup & MAUDIO_SET_MASK;
		if (mask == MAUDIO_SET_24B_48K_DI && altno != 2)
			return 1; /* skip this altsetting */
		if (mask == MAUDIO_SET_24B_48K_NOTDI && altno != 3)
			return 1; /* skip this altsetting */
		if (mask == MAUDIO_SET_16B_48K_DI && altno != 4)
			return 1; /* skip this altsetting */
		if (mask == MAUDIO_SET_16B_48K_NOTDI && altno != 5)
			return 1; /* skip this altsetting */
	}

	return 0; /* keep this altsetting */
}
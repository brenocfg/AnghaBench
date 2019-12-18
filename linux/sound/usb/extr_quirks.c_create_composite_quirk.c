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
struct usb_interface {int /*<<< orphan*/  altsetting; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio_quirk {int ifnum; struct snd_usb_audio_quirk* data; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int bInterfaceNumber; } ;

/* Variables and functions */
 TYPE_1__* get_iface_desc (int /*<<< orphan*/ ) ; 
 int snd_usb_create_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*,struct snd_usb_audio_quirk const*) ; 
 int /*<<< orphan*/  usb_driver_claim_interface (struct usb_driver*,struct usb_interface*,void*) ; 
 struct usb_interface* usb_ifnum_to_if (int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_interface_claimed (struct usb_interface*) ; 

__attribute__((used)) static int create_composite_quirk(struct snd_usb_audio *chip,
				  struct usb_interface *iface,
				  struct usb_driver *driver,
				  const struct snd_usb_audio_quirk *quirk_comp)
{
	int probed_ifnum = get_iface_desc(iface->altsetting)->bInterfaceNumber;
	const struct snd_usb_audio_quirk *quirk;
	int err;

	for (quirk = quirk_comp->data; quirk->ifnum >= 0; ++quirk) {
		iface = usb_ifnum_to_if(chip->dev, quirk->ifnum);
		if (!iface)
			continue;
		if (quirk->ifnum != probed_ifnum &&
		    usb_interface_claimed(iface))
			continue;
		err = snd_usb_create_quirk(chip, iface, driver, quirk);
		if (err < 0)
			return err;
	}

	for (quirk = quirk_comp->data; quirk->ifnum >= 0; ++quirk) {
		iface = usb_ifnum_to_if(chip->dev, quirk->ifnum);
		if (!iface)
			continue;
		if (quirk->ifnum != probed_ifnum &&
		    !usb_interface_claimed(iface))
			usb_driver_claim_interface(driver, iface, (void *)-1L);
	}

	return 0;
}
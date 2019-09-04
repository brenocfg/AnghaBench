#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  altsetting; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio_quirk {scalar_t__ ifnum; } ;
struct snd_usb_audio {TYPE_3__* dev; } ;
struct TYPE_8__ {int bInterfaceNumber; scalar_t__ bInterfaceClass; } ;
struct TYPE_7__ {TYPE_2__* actconfig; } ;
struct TYPE_5__ {int bNumInterfaces; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int create_autodetect_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*) ; 
 TYPE_4__* get_iface_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_claim_interface (struct usb_driver*,struct usb_interface*,void*) ; 
 struct usb_interface* usb_ifnum_to_if (TYPE_3__*,int) ; 
 scalar_t__ usb_interface_claimed (struct usb_interface*) ; 

__attribute__((used)) static int create_autodetect_quirks(struct snd_usb_audio *chip,
				    struct usb_interface *iface,
				    struct usb_driver *driver,
				    const struct snd_usb_audio_quirk *quirk)
{
	int probed_ifnum = get_iface_desc(iface->altsetting)->bInterfaceNumber;
	int ifcount, ifnum, err;

	err = create_autodetect_quirk(chip, iface, driver);
	if (err < 0)
		return err;

	/*
	 * ALSA PCM playback/capture devices cannot be registered in two steps,
	 * so we have to claim the other corresponding interface here.
	 */
	ifcount = chip->dev->actconfig->desc.bNumInterfaces;
	for (ifnum = 0; ifnum < ifcount; ifnum++) {
		if (ifnum == probed_ifnum || quirk->ifnum >= 0)
			continue;
		iface = usb_ifnum_to_if(chip->dev, ifnum);
		if (!iface ||
		    usb_interface_claimed(iface) ||
		    get_iface_desc(iface->altsetting)->bInterfaceClass !=
							USB_CLASS_VENDOR_SPEC)
			continue;

		err = create_autodetect_quirk(chip, iface, driver);
		if (err >= 0)
			usb_driver_claim_interface(driver, iface, (void *)-1L);
	}

	return 0;
}
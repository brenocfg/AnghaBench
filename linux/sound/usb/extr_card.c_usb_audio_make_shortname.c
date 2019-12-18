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
struct TYPE_2__ {int /*<<< orphan*/  iProduct; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct snd_usb_audio_quirk {scalar_t__* product_name; } ;
struct snd_usb_audio {int /*<<< orphan*/  usb_id; struct snd_card* card; } ;
struct snd_card {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 int USB_ID_PRODUCT (int /*<<< orphan*/ ) ; 
 int USB_ID_VENDOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  strim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ usb_string (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_audio_make_shortname(struct usb_device *dev,
				     struct snd_usb_audio *chip,
				     const struct snd_usb_audio_quirk *quirk)
{
	struct snd_card *card = chip->card;

	if (quirk && quirk->product_name && *quirk->product_name) {
		strlcpy(card->shortname, quirk->product_name,
			sizeof(card->shortname));
		return;
	}

	/* retrieve the device string as shortname */
	if (!dev->descriptor.iProduct ||
	    usb_string(dev, dev->descriptor.iProduct,
		       card->shortname, sizeof(card->shortname)) <= 0) {
		/* no name available from anywhere, so use ID */
		sprintf(card->shortname, "USB Device %#04x:%#04x",
			USB_ID_VENDOR(chip->usb_id),
			USB_ID_PRODUCT(chip->usb_id));
	}

	strim(card->shortname);
}
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
struct usb_device_id {int match_flags; scalar_t__ idVendor; scalar_t__ idProduct; scalar_t__ driver_info; } ;
struct usb_device {int dummy; } ;
struct snd_usb_audio_quirk {int dummy; } ;

/* Variables and functions */
 int USB_DEVICE_ID_MATCH_DEVICE ; 
 scalar_t__ USB_ID_PRODUCT (unsigned int) ; 
 scalar_t__ USB_ID_VENDOR (unsigned int) ; 
 struct usb_device_id* usb_audio_ids ; 

__attribute__((used)) static const struct snd_usb_audio_quirk *
get_alias_quirk(struct usb_device *dev, unsigned int id)
{
	const struct usb_device_id *p;

	for (p = usb_audio_ids; p->match_flags; p++) {
		/* FIXME: this checks only vendor:product pair in the list */
		if ((p->match_flags & USB_DEVICE_ID_MATCH_DEVICE) ==
		    USB_DEVICE_ID_MATCH_DEVICE &&
		    p->idVendor == USB_ID_VENDOR(id) &&
		    p->idProduct == USB_ID_PRODUCT(id))
			return (const struct snd_usb_audio_quirk *)p->driver_info;
	}

	return NULL;
}
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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB_ID_US122 ; 
 int USB_ID_US224 ; 
 int USB_ID_US428 ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_register (struct snd_card*) ; 
 int usX2Y_create_card (struct usb_device*,struct usb_interface*,struct snd_card**) ; 
 int usX2Y_hwdep_new (struct snd_card*,struct usb_device*) ; 

__attribute__((used)) static int usX2Y_usb_probe(struct usb_device *device,
			   struct usb_interface *intf,
			   const struct usb_device_id *device_id,
			   struct snd_card **cardp)
{
	int		err;
	struct snd_card *	card;

	*cardp = NULL;
	if (le16_to_cpu(device->descriptor.idVendor) != 0x1604 ||
	    (le16_to_cpu(device->descriptor.idProduct) != USB_ID_US122 &&
	     le16_to_cpu(device->descriptor.idProduct) != USB_ID_US224 &&
	     le16_to_cpu(device->descriptor.idProduct) != USB_ID_US428))
		return -EINVAL;

	err = usX2Y_create_card(device, intf, &card);
	if (err < 0)
		return err;
	if ((err = usX2Y_hwdep_new(card, device)) < 0  ||
	    (err = snd_card_register(card)) < 0) {
		snd_card_free(card);
		return err;
	}
	*cardp = card;
	return 0;
}
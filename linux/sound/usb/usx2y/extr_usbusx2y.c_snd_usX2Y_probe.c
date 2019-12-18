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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_card*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int usX2Y_usb_probe (int /*<<< orphan*/ ,struct usb_interface*,struct usb_device_id const*,struct snd_card**) ; 

__attribute__((used)) static int snd_usX2Y_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct snd_card *card;
	int err;

	err = usX2Y_usb_probe(interface_to_usbdev(intf), intf, id, &card);
	if (err < 0)
		return err;
	dev_set_drvdata(&intf->dev, card);
	return 0;
}
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
struct port100 {int /*<<< orphan*/  cmd; int /*<<< orphan*/  udev; int /*<<< orphan*/  out_urb; int /*<<< orphan*/  in_urb; int /*<<< orphan*/  nfc_digital_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_free_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_digital_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct port100* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void port100_disconnect(struct usb_interface *interface)
{
	struct port100 *dev;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	nfc_digital_unregister_device(dev->nfc_digital_dev);
	nfc_digital_free_device(dev->nfc_digital_dev);

	usb_kill_urb(dev->in_urb);
	usb_kill_urb(dev->out_urb);

	usb_free_urb(dev->in_urb);
	usb_free_urb(dev->out_urb);
	usb_put_dev(dev->udev);

	kfree(dev->cmd);

	nfc_info(&interface->dev, "Sony Port-100 NFC device disconnected\n");
}
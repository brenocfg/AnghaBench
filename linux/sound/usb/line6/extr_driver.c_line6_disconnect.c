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
struct usb_line6 {int /*<<< orphan*/  card; TYPE_1__* properties; int /*<<< orphan*/  (* disconnect ) (struct usb_line6*) ;scalar_t__ line6pcm; int /*<<< orphan*/ * urb_listen; int /*<<< orphan*/  startup_work; struct usb_device* usbdev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  line6_pcm_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  line6_stop_listen (struct usb_line6*) ; 
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_line6*) ; 
 struct usb_line6* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

void line6_disconnect(struct usb_interface *interface)
{
	struct usb_line6 *line6 = usb_get_intfdata(interface);
	struct usb_device *usbdev = interface_to_usbdev(interface);

	if (!line6)
		return;

	if (WARN_ON(usbdev != line6->usbdev))
		return;

	cancel_delayed_work(&line6->startup_work);

	if (line6->urb_listen != NULL)
		line6_stop_listen(line6);

	snd_card_disconnect(line6->card);
	if (line6->line6pcm)
		line6_pcm_disconnect(line6->line6pcm);
	if (line6->disconnect)
		line6->disconnect(line6);

	dev_info(&interface->dev, "Line 6 %s now disconnected\n",
		 line6->properties->name);

	/* make sure the device isn't destructed twice: */
	usb_set_intfdata(interface, NULL);

	snd_card_free_when_closed(line6->card);
}
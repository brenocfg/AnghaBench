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
struct usb_line6 {int /*<<< orphan*/ * urb_listen; int /*<<< orphan*/  buffer_listen; int /*<<< orphan*/  buffer_message; struct usb_device* usbdev; } ;
struct usb_device {int dummy; } ;
struct snd_card {struct usb_line6* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void line6_destruct(struct snd_card *card)
{
	struct usb_line6 *line6 = card->private_data;
	struct usb_device *usbdev = line6->usbdev;

	/* Free buffer memory first. We cannot depend on the existence of private
	 * data from the (podhd) module, it may be gone already during this call
	 */
	kfree(line6->buffer_message);

	kfree(line6->buffer_listen);

	/* then free URBs: */
	usb_free_urb(line6->urb_listen);
	line6->urb_listen = NULL;

	/* decrement reference counters: */
	usb_put_dev(usbdev);
}
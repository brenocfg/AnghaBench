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
struct usb_onetouch {int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; int /*<<< orphan*/  udev; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ONETOUCH_PKT_LEN ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onetouch_release_input(void *onetouch_)
{
	struct usb_onetouch *onetouch = (struct usb_onetouch *) onetouch_;

	if (onetouch) {
		usb_kill_urb(onetouch->irq);
		input_unregister_device(onetouch->dev);
		usb_free_urb(onetouch->irq);
		usb_free_coherent(onetouch->udev, ONETOUCH_PKT_LEN,
				  onetouch->data, onetouch->data_dma);
	}
}
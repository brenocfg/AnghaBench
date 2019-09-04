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
struct usb_sg_request {size_t entries; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sg_clean(struct usb_sg_request *io)
{
	if (io->urbs) {
		while (io->entries--)
			usb_free_urb(io->urbs[io->entries]);
		kfree(io->urbs);
		io->urbs = NULL;
	}
	io->dev = NULL;
}
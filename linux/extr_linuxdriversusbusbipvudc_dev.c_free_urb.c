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
struct urb {int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/ * setup_packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void free_urb(struct urb *urb)
{
	if (!urb)
		return;

	kfree(urb->setup_packet);
	urb->setup_packet = NULL;

	kfree(urb->transfer_buffer);
	urb->transfer_buffer = NULL;

	usb_free_urb(urb);
}
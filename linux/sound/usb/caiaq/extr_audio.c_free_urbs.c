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
struct urb {struct urb** transfer_buffer; } ;

/* Variables and functions */
 int N_URBS ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void free_urbs(struct urb **urbs)
{
	int i;

	if (!urbs)
		return;

	for (i = 0; i < N_URBS; i++) {
		if (!urbs[i])
			continue;

		usb_kill_urb(urbs[i]);
		kfree(urbs[i]->transfer_buffer);
		usb_free_urb(urbs[i]);
	}

	kfree(urbs);
}
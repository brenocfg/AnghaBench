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
struct ath6kl_usb {TYPE_1__* pipes; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb_submitted; int /*<<< orphan*/ * ar_usb; } ;

/* Variables and functions */
 int ATH6KL_USB_PIPE_MAX ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_usb_flush_all(struct ath6kl_usb *ar_usb)
{
	int i;

	for (i = 0; i < ATH6KL_USB_PIPE_MAX; i++) {
		if (ar_usb->pipes[i].ar_usb != NULL)
			usb_kill_anchored_urbs(&ar_usb->pipes[i].urb_submitted);
	}

	/*
	 * Flushing any pending I/O may schedule work this call will block
	 * until all scheduled work runs to completion.
	 */
	flush_scheduled_work();
}
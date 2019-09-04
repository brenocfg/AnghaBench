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
struct ath10k_usb {TYPE_1__* pipes; } ;
struct ath10k {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  io_complete_work; int /*<<< orphan*/  urb_submitted; scalar_t__ ar_usb; } ;

/* Variables and functions */
 int ATH10K_USB_PIPE_MAX ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_usb_flush_all(struct ath10k *ar)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	int i;

	for (i = 0; i < ATH10K_USB_PIPE_MAX; i++) {
		if (ar_usb->pipes[i].ar_usb) {
			usb_kill_anchored_urbs(&ar_usb->pipes[i].urb_submitted);
			cancel_work_sync(&ar_usb->pipes[i].io_complete_work);
		}
	}
}
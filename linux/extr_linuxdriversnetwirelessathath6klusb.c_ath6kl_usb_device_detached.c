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
struct usb_interface {int dummy; } ;
struct ath6kl_usb {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_core_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_stop_txrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_usb_destroy (struct ath6kl_usb*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct ath6kl_usb* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void ath6kl_usb_device_detached(struct usb_interface *interface)
{
	struct ath6kl_usb *ar_usb;

	ar_usb = usb_get_intfdata(interface);
	if (ar_usb == NULL)
		return;

	ath6kl_stop_txrx(ar_usb->ar);

	/* Delay to wait for the target to reboot */
	mdelay(20);
	ath6kl_core_cleanup(ar_usb->ar);
	ath6kl_usb_destroy(ar_usb);
}
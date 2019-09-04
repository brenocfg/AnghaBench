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
struct ath10k_usb {int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_core_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_core_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_usb_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 struct ath10k_usb* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_usb_remove(struct usb_interface *interface)
{
	struct ath10k_usb *ar_usb;

	ar_usb = usb_get_intfdata(interface);
	if (!ar_usb)
		return;

	ath10k_core_unregister(ar_usb->ar);
	ath10k_usb_destroy(ar_usb->ar);
	usb_put_dev(interface_to_usbdev(interface));
	ath10k_core_destroy(ar_usb->ar);
}
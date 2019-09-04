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
struct bcd2000 {int /*<<< orphan*/ * intf; int /*<<< orphan*/  midi_in_urb; int /*<<< orphan*/  midi_out_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcd2000_free_usb_related_resources(struct bcd2000 *bcd2k,
						struct usb_interface *interface)
{
	/* usb_kill_urb not necessary, urb is aborted automatically */

	usb_free_urb(bcd2k->midi_out_urb);
	usb_free_urb(bcd2k->midi_in_urb);

	if (bcd2k->intf) {
		usb_set_intfdata(bcd2k->intf, NULL);
		bcd2k->intf = NULL;
	}
}
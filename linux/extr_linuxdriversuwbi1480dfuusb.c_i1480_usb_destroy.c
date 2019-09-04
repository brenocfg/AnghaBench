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
struct i1480_usb {int /*<<< orphan*/  usb_dev; int /*<<< orphan*/  usb_iface; int /*<<< orphan*/  neep_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_intf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void i1480_usb_destroy(struct i1480_usb *i1480_usb)
{
	usb_kill_urb(i1480_usb->neep_urb);
	usb_free_urb(i1480_usb->neep_urb);
	usb_set_intfdata(i1480_usb->usb_iface, NULL);
	usb_put_intf(i1480_usb->usb_iface);
	usb_put_dev(i1480_usb->usb_dev);
}
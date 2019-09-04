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
struct usb_hcd {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* _hcd ; 
 struct usb_hcd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rh_timer ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (struct usb_hcd*) ; 

__attribute__((used)) static void rh_timer_func (struct timer_list *t)
{
	struct usb_hcd *_hcd = from_timer(_hcd, t, rh_timer);

	usb_hcd_poll_rh_status(_hcd);
}
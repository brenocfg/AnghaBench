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
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int usb3_set_halt (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usb_ep_to_usb3_ep (struct usb_ep*) ; 

__attribute__((used)) static int renesas_usb3_ep_set_halt(struct usb_ep *_ep, int value)
{
	return usb3_set_halt(usb_ep_to_usb3_ep(_ep), !!value, false);
}
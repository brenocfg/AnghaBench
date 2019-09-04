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
struct usb_function {int /*<<< orphan*/  (* free_func ) (struct usb_function*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usb_function*) ; 

void usb_put_function(struct usb_function *f)
{
	if (!f)
		return;

	f->free_func(f);
}
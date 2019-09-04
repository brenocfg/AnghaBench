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
struct usb_function {int dummy; } ;
struct f_obex {int cur_alt; } ;

/* Variables and functions */
 struct f_obex* func_to_obex (struct usb_function*) ; 

__attribute__((used)) static int obex_get_alt(struct usb_function *f, unsigned intf)
{
	struct f_obex		*obex = func_to_obex(f);

	return obex->cur_alt;
}
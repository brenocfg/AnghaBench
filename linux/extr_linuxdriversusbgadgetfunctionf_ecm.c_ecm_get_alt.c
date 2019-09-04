#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_function {int dummy; } ;
struct TYPE_4__ {TYPE_1__* in_ep; } ;
struct f_ecm {unsigned int ctrl_id; TYPE_2__ port; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;

/* Variables and functions */
 struct f_ecm* func_to_ecm (struct usb_function*) ; 

__attribute__((used)) static int ecm_get_alt(struct usb_function *f, unsigned intf)
{
	struct f_ecm		*ecm = func_to_ecm(f);

	if (intf == ecm->ctrl_id)
		return 0;
	return ecm->port.in_ep->enabled ? 1 : 0;
}
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
struct usba_udc {scalar_t__ vbus_pin; } ;

/* Variables and functions */
 int gpiod_get_value (scalar_t__) ; 

__attribute__((used)) static int vbus_is_present(struct usba_udc *udc)
{
	if (udc->vbus_pin)
		return gpiod_get_value(udc->vbus_pin);

	/* No Vbus detection: Assume always present */
	return 1;
}
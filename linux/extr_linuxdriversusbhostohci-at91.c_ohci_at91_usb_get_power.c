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
struct at91_usbh_data {int /*<<< orphan*/ * vbus_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_port (int) ; 

__attribute__((used)) static int ohci_at91_usb_get_power(struct at91_usbh_data *pdata, int port)
{
	if (!valid_port(port))
		return -EINVAL;

	return gpiod_get_value(pdata->vbus_pin[port]);
}
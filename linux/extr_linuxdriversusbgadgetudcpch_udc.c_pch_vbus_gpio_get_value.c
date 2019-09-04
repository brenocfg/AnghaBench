#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ port; } ;
struct pch_udc_dev {TYPE_1__ vbus_gpio; } ;

/* Variables and functions */
 scalar_t__ gpio_get_value (scalar_t__) ; 

__attribute__((used)) static int pch_vbus_gpio_get_value(struct pch_udc_dev *dev)
{
	int vbus = 0;

	if (dev->vbus_gpio.port)
		vbus = gpio_get_value(dev->vbus_gpio.port) ? 1 : 0;
	else
		vbus = -1;

	return vbus;
}
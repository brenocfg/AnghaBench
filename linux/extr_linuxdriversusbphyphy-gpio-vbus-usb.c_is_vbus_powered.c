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
struct gpio_vbus_mach_info {scalar_t__ gpio_vbus_inverted; int /*<<< orphan*/  gpio_vbus; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_vbus_powered(struct gpio_vbus_mach_info *pdata)
{
	int vbus;

	vbus = gpio_get_value(pdata->gpio_vbus);
	if (pdata->gpio_vbus_inverted)
		vbus = !vbus;

	return vbus;
}
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

/* Variables and functions */
 scalar_t__* devices ; 
 int nr_devices ; 
 int /*<<< orphan*/  platform_device_put (scalar_t__) ; 

__attribute__((used)) static void i2c_gpio_custom_cleanup(void)
{
	int i;

	for (i = 0; i < nr_devices; i++)
		if (devices[i])
			platform_device_put(devices[i]);
}
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
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_gpio_driver ; 

int viafb_gpio_init(void)
{
	return platform_driver_register(&via_gpio_driver);
}
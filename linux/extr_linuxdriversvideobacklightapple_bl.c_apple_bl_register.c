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
 int acpi_bus_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apple_bl_driver ; 
 int /*<<< orphan*/  apple_bl_registered ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 

int apple_bl_register(void)
{
	if (atomic_xchg(&apple_bl_registered, 1) == 0)
		return acpi_bus_register_driver(&apple_bl_driver);

	return 0;
}
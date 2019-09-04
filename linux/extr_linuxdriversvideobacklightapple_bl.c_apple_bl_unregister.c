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
 int /*<<< orphan*/  acpi_bus_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apple_bl_driver ; 
 int /*<<< orphan*/  apple_bl_registered ; 
 int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void apple_bl_unregister(void)
{
	if (atomic_xchg(&apple_bl_registered, 0) == 1)
		acpi_bus_unregister_driver(&apple_bl_driver);
}
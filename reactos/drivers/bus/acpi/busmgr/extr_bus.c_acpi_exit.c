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
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  acpi_bus_exit () ; 
 scalar_t__ pm_active ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_exit (void)
{
	DPRINT("acpi_exit\n");

#ifdef CONFIG_PM
	pm_active = 0;
#endif

	acpi_bus_exit();

	return_VOID;
}
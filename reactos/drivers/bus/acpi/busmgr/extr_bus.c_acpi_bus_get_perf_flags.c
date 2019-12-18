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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct acpi_device {TYPE_1__ performance; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_STATE_UNKNOWN ; 
 int AE_NOT_FOUND ; 

__attribute__((used)) static int
acpi_bus_get_perf_flags (
	struct acpi_device	*device)
{
	if (!device)
		return AE_NOT_FOUND;

	device->performance.state = ACPI_STATE_UNKNOWN;

	return 0;
}
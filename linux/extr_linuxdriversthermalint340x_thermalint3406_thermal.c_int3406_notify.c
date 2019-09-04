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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ INT3406_BRIGHTNESS_LIMITS_CHANGED ; 
 int /*<<< orphan*/  int3406_thermal_get_limit (void*) ; 

__attribute__((used)) static void int3406_notify(acpi_handle handle, u32 event, void *data)
{
	if (event == INT3406_BRIGHTNESS_LIMITS_CHANGED)
		int3406_thermal_get_limit(data);
}
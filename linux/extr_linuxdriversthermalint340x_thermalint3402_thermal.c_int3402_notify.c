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
typedef  int u32 ;
struct int3402_thermal_data {int /*<<< orphan*/  int340x_zone; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  INT3402_PERF_CHANGED_EVENT 129 
#define  INT3402_THERMAL_EVENT 128 
 int /*<<< orphan*/  THERMAL_TRIP_VIOLATED ; 
 int /*<<< orphan*/  int340x_thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int3402_notify(acpi_handle handle, u32 event, void *data)
{
	struct int3402_thermal_data *priv = data;

	if (!priv)
		return;

	switch (event) {
	case INT3402_PERF_CHANGED_EVENT:
		break;
	case INT3402_THERMAL_EVENT:
		int340x_thermal_zone_device_update(priv->int340x_zone,
						   THERMAL_TRIP_VIOLATED);
		break;
	default:
		break;
	}
}
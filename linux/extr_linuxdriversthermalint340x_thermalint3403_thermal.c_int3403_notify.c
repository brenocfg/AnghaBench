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
typedef  int u32 ;
struct int3403_sensor {int /*<<< orphan*/  int340x_zone; } ;
struct int3403_priv {scalar_t__ type; TYPE_1__* pdev; struct int3403_sensor* priv; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  INT3403_PERF_CHANGED_EVENT 130 
#define  INT3403_PERF_TRIP_POINT_CHANGED 129 
#define  INT3403_THERMAL_EVENT 128 
 scalar_t__ INT3403_TYPE_SENSOR ; 
 int /*<<< orphan*/  THERMAL_TRIP_CHANGED ; 
 int /*<<< orphan*/  THERMAL_TRIP_VIOLATED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  int340x_thermal_read_trips (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int340x_thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int3403_notify(acpi_handle handle,
		u32 event, void *data)
{
	struct int3403_priv *priv = data;
	struct int3403_sensor *obj;

	if (!priv)
		return;

	obj = priv->priv;
	if (priv->type != INT3403_TYPE_SENSOR || !obj)
		return;

	switch (event) {
	case INT3403_PERF_CHANGED_EVENT:
		break;
	case INT3403_THERMAL_EVENT:
		int340x_thermal_zone_device_update(obj->int340x_zone,
						   THERMAL_TRIP_VIOLATED);
		break;
	case INT3403_PERF_TRIP_POINT_CHANGED:
		int340x_thermal_read_trips(obj->int340x_zone);
		int340x_thermal_zone_device_update(obj->int340x_zone,
						   THERMAL_TRIP_CHANGED);
		break;
	default:
		dev_err(&priv->pdev->dev, "Unsupported event [0x%x]\n", event);
		break;
	}
}
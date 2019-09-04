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
struct int3403_sensor {int /*<<< orphan*/  int340x_zone; } ;
struct int3403_priv {TYPE_1__* adev; struct int3403_sensor* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3403_notify ; 
 int /*<<< orphan*/  int340x_thermal_zone_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int3403_sensor_remove(struct int3403_priv *priv)
{
	struct int3403_sensor *obj = priv->priv;

	acpi_remove_notify_handler(priv->adev->handle,
				   ACPI_DEVICE_NOTIFY, int3403_notify);
	int340x_thermal_zone_remove(obj->int340x_zone);

	return 0;
}
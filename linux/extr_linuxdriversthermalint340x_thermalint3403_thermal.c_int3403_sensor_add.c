#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct int3403_sensor {int /*<<< orphan*/  int340x_zone; } ;
struct int3403_priv {TYPE_2__* adev; struct int3403_sensor* priv; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct int3403_sensor* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3403_notify ; 
 int /*<<< orphan*/  int340x_thermal_zone_add (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int340x_thermal_zone_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int int3403_sensor_add(struct int3403_priv *priv)
{
	int result = 0;
	struct int3403_sensor *obj;

	obj = devm_kzalloc(&priv->pdev->dev, sizeof(*obj), GFP_KERNEL);
	if (!obj)
		return -ENOMEM;

	priv->priv = obj;

	obj->int340x_zone = int340x_thermal_zone_add(priv->adev, NULL);
	if (IS_ERR(obj->int340x_zone))
		return PTR_ERR(obj->int340x_zone);

	result = acpi_install_notify_handler(priv->adev->handle,
			ACPI_DEVICE_NOTIFY, int3403_notify,
			(void *)priv);
	if (result)
		goto err_free_obj;

	return 0;

 err_free_obj:
	int340x_thermal_zone_remove(obj->int340x_zone);
	return result;
}
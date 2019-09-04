#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fujitsu_laptop {TYPE_2__* pf_device; } ;
struct acpi_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fujitsu_laptop* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  fujitsu_pf_attribute_group ; 
 int platform_device_add (TYPE_2__*) ; 
 TYPE_2__* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (TYPE_2__*,struct fujitsu_laptop*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fujitsu_laptop_platform_add(struct acpi_device *device)
{
	struct fujitsu_laptop *priv = acpi_driver_data(device);
	int ret;

	priv->pf_device = platform_device_alloc("fujitsu-laptop", -1);
	if (!priv->pf_device)
		return -ENOMEM;

	platform_set_drvdata(priv->pf_device, priv);

	ret = platform_device_add(priv->pf_device);
	if (ret)
		goto err_put_platform_device;

	ret = sysfs_create_group(&priv->pf_device->dev.kobj,
				 &fujitsu_pf_attribute_group);
	if (ret)
		goto err_del_platform_device;

	return 0;

err_del_platform_device:
	platform_device_del(priv->pf_device);
err_put_platform_device:
	platform_device_put(priv->pf_device);

	return ret;
}
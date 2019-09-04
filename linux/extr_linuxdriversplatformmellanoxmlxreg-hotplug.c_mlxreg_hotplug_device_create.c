#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlxreg_hotplug_priv_data {int /*<<< orphan*/  dev; TYPE_2__* pdev; TYPE_1__* hwmon; } ;
struct mlxreg_core_hotplug_platform_data {scalar_t__ shift_nr; } ;
struct TYPE_7__ {scalar_t__ nr; int /*<<< orphan*/ * adapter; TYPE_4__* brdinfo; int /*<<< orphan*/  client; } ;
struct mlxreg_core_data {TYPE_3__ hpdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 struct mlxreg_core_hotplug_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i2c_get_adapter (scalar_t__) ; 
 int /*<<< orphan*/  i2c_new_device (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxreg_hotplug_device_create(struct mlxreg_hotplug_priv_data *priv,
					struct mlxreg_core_data *data)
{
	struct mlxreg_core_hotplug_platform_data *pdata;

	/* Notify user by sending hwmon uevent. */
	kobject_uevent(&priv->hwmon->kobj, KOBJ_CHANGE);

	/*
	 * Return if adapter number is negative. It could be in case hotplug
	 * event is not associated with hotplug device.
	 */
	if (data->hpdev.nr < 0)
		return 0;

	pdata = dev_get_platdata(&priv->pdev->dev);
	data->hpdev.adapter = i2c_get_adapter(data->hpdev.nr +
					      pdata->shift_nr);
	if (!data->hpdev.adapter) {
		dev_err(priv->dev, "Failed to get adapter for bus %d\n",
			data->hpdev.nr + pdata->shift_nr);
		return -EFAULT;
	}

	data->hpdev.client = i2c_new_device(data->hpdev.adapter,
					    data->hpdev.brdinfo);
	if (!data->hpdev.client) {
		dev_err(priv->dev, "Failed to create client %s at bus %d at addr 0x%02x\n",
			data->hpdev.brdinfo->type, data->hpdev.nr +
			pdata->shift_nr, data->hpdev.brdinfo->addr);

		i2c_put_adapter(data->hpdev.adapter);
		data->hpdev.adapter = NULL;
		return -EFAULT;
	}

	return 0;
}
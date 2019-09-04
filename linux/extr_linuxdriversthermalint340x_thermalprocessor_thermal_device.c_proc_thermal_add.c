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
struct thermal_zone_device_ops {int dummy; } ;
struct proc_thermal_device {int /*<<< orphan*/  int340x_zone; struct acpi_device* adev; struct device* dev; } ;
struct device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct proc_thermal_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_tjmax () ; 
 int /*<<< orphan*/  int340x_thermal_zone_add (struct acpi_device*,struct thermal_zone_device_ops*) ; 
 int /*<<< orphan*/  int340x_thermal_zone_remove (int /*<<< orphan*/ ) ; 
 struct thermal_zone_device_ops proc_thermal_local_ops ; 
 int /*<<< orphan*/  proc_thermal_notify ; 
 int proc_thermal_read_ppcc (struct proc_thermal_device*) ; 
 scalar_t__ stored_tjmax ; 

__attribute__((used)) static int proc_thermal_add(struct device *dev,
			    struct proc_thermal_device **priv)
{
	struct proc_thermal_device *proc_priv;
	struct acpi_device *adev;
	acpi_status status;
	unsigned long long tmp;
	struct thermal_zone_device_ops *ops = NULL;
	int ret;

	adev = ACPI_COMPANION(dev);
	if (!adev)
		return -ENODEV;

	proc_priv = devm_kzalloc(dev, sizeof(*proc_priv), GFP_KERNEL);
	if (!proc_priv)
		return -ENOMEM;

	proc_priv->dev = dev;
	proc_priv->adev = adev;
	*priv = proc_priv;

	ret = proc_thermal_read_ppcc(proc_priv);
	if (ret)
		return ret;

	status = acpi_evaluate_integer(adev->handle, "_TMP", NULL, &tmp);
	if (ACPI_FAILURE(status)) {
		/* there is no _TMP method, add local method */
		stored_tjmax = get_tjmax();
		if (stored_tjmax > 0)
			ops = &proc_thermal_local_ops;
	}

	proc_priv->int340x_zone = int340x_thermal_zone_add(adev, ops);
	if (IS_ERR(proc_priv->int340x_zone)) {
		return PTR_ERR(proc_priv->int340x_zone);
	} else
		ret = 0;

	ret = acpi_install_notify_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					  proc_thermal_notify,
					  (void *)proc_priv);
	if (ret)
		goto remove_zone;

	return 0;

remove_zone:
	int340x_thermal_zone_remove(proc_priv->int340x_zone);

	return ret;
}
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
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_4__ integer; TYPE_2__ package; } ;
struct proc_thermal_device {TYPE_3__* power_limits; int /*<<< orphan*/  dev; TYPE_1__* adev; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_7__ {int /*<<< orphan*/  step_uw; int /*<<< orphan*/  tmax_us; int /*<<< orphan*/  tmin_us; int /*<<< orphan*/  max_uw; int /*<<< orphan*/  min_uw; int /*<<< orphan*/  index; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int min (int,int) ; 

__attribute__((used)) static int proc_thermal_read_ppcc(struct proc_thermal_device *proc_priv)
{
	int i;
	acpi_status status;
	struct acpi_buffer buf = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *elements, *ppcc;
	union acpi_object *p;
	int ret = 0;

	status = acpi_evaluate_object(proc_priv->adev->handle, "PPCC",
				      NULL, &buf);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	p = buf.pointer;
	if (!p || (p->type != ACPI_TYPE_PACKAGE)) {
		dev_err(proc_priv->dev, "Invalid PPCC data\n");
		ret = -EFAULT;
		goto free_buffer;
	}

	if (!p->package.count) {
		dev_err(proc_priv->dev, "Invalid PPCC package size\n");
		ret = -EFAULT;
		goto free_buffer;
	}

	for (i = 0; i < min((int)p->package.count - 1, 2); ++i) {
		elements = &(p->package.elements[i+1]);
		if (elements->type != ACPI_TYPE_PACKAGE ||
		    elements->package.count != 6) {
			ret = -EFAULT;
			goto free_buffer;
		}
		ppcc = elements->package.elements;
		proc_priv->power_limits[i].index = ppcc[0].integer.value;
		proc_priv->power_limits[i].min_uw = ppcc[1].integer.value;
		proc_priv->power_limits[i].max_uw = ppcc[2].integer.value;
		proc_priv->power_limits[i].tmin_us = ppcc[3].integer.value;
		proc_priv->power_limits[i].tmax_us = ppcc[4].integer.value;
		proc_priv->power_limits[i].step_uw = ppcc[5].integer.value;
	}

free_buffer:
	kfree(buf.pointer);

	return ret;
}
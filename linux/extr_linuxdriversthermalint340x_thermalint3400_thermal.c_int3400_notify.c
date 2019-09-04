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
typedef  int u32 ;
struct int3400_thermal_priv {TYPE_2__* thermal; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ device; int /*<<< orphan*/  temperature; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  INT3400_THERMAL_TABLE_CHANGED 128 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  THERMAL_TABLE_CHANGED ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void int3400_notify(acpi_handle handle,
			u32 event,
			void *data)
{
	struct int3400_thermal_priv *priv = data;
	char *thermal_prop[5];

	if (!priv)
		return;

	switch (event) {
	case INT3400_THERMAL_TABLE_CHANGED:
		thermal_prop[0] = kasprintf(GFP_KERNEL, "NAME=%s",
				priv->thermal->type);
		thermal_prop[1] = kasprintf(GFP_KERNEL, "TEMP=%d",
				priv->thermal->temperature);
		thermal_prop[2] = kasprintf(GFP_KERNEL, "TRIP=");
		thermal_prop[3] = kasprintf(GFP_KERNEL, "EVENT=%d",
				THERMAL_TABLE_CHANGED);
		thermal_prop[4] = NULL;
		kobject_uevent_env(&priv->thermal->device.kobj, KOBJ_CHANGE,
				thermal_prop);
		break;
	default:
		/* Ignore unknown notification codes sent to INT3400 device */
		break;
	}
}
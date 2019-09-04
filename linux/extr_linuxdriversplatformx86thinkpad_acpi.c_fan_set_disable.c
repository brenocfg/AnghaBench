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
struct TYPE_2__ {int /*<<< orphan*/  fan_ctrl_status_undef; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TPACPI_DBG_FAN ; 
#define  TPACPI_FAN_WR_ACPI_FANS 130 
#define  TPACPI_FAN_WR_ACPI_SFAN 129 
#define  TPACPI_FAN_WR_TPEC 128 
 int /*<<< orphan*/  acpi_ec_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int fan_control_access_mode ; 
 int /*<<< orphan*/  fan_control_allowed ; 
 int /*<<< orphan*/  fan_control_desired_level ; 
 int /*<<< orphan*/  fan_mutex ; 
 int /*<<< orphan*/  fan_status_offset ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfan_handle ; 
 TYPE_1__ tp_features ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fan_set_disable(void)
{
	int rc;

	if (!fan_control_allowed)
		return -EPERM;

	if (mutex_lock_killable(&fan_mutex))
		return -ERESTARTSYS;

	rc = 0;
	switch (fan_control_access_mode) {
	case TPACPI_FAN_WR_ACPI_FANS:
	case TPACPI_FAN_WR_TPEC:
		if (!acpi_ec_write(fan_status_offset, 0x00))
			rc = -EIO;
		else {
			fan_control_desired_level = 0;
			tp_features.fan_ctrl_status_undef = 0;
		}
		break;

	case TPACPI_FAN_WR_ACPI_SFAN:
		if (!acpi_evalf(sfan_handle, NULL, NULL, "vd", 0x00))
			rc = -EIO;
		else
			fan_control_desired_level = 0;
		break;

	default:
		rc = -ENXIO;
	}

	if (!rc)
		vdbg_printk(TPACPI_DBG_FAN,
			"fan control: set fan control register to 0\n");

	mutex_unlock(&fan_mutex);
	return rc;
}
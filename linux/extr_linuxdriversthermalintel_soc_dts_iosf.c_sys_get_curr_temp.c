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
struct thermal_zone_device {struct intel_soc_dts_sensor_entry* devdata; } ;
struct intel_soc_dts_sensors {int tj_max; } ;
struct intel_soc_dts_sensor_entry {int temp_mask; int temp_shift; struct intel_soc_dts_sensors* sensors; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  SOC_DTS_OFFSET_TEMP ; 
 scalar_t__ SOC_DTS_TJMAX_ENCODING ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sys_get_curr_temp(struct thermal_zone_device *tzd,
			     int *temp)
{
	int status;
	u32 out;
	struct intel_soc_dts_sensor_entry *dts;
	struct intel_soc_dts_sensors *sensors;

	dts = tzd->devdata;
	sensors = dts->sensors;
	status = iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ,
			       SOC_DTS_OFFSET_TEMP, &out);
	if (status)
		return status;

	out = (out & dts->temp_mask) >> dts->temp_shift;
	out -= SOC_DTS_TJMAX_ENCODING;
	*temp = sensors->tj_max - out * 1000;

	return 0;
}
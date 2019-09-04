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
struct thermal_zone_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBI_REG_READ ; 
 int QRK_DTS_MASK_TEMP ; 
 int QRK_DTS_OFFSET_TEMP ; 
 int /*<<< orphan*/  QRK_DTS_REG_OFFSET_TEMP ; 
 int QRK_DTS_TEMP_BASE ; 
 int /*<<< orphan*/  QRK_MBI_UNIT_RMU ; 
 int /*<<< orphan*/  dts_update_mutex ; 
 int iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sys_get_curr_temp(struct thermal_zone_device *tzd,
				int *temp)
{
	u32 out;
	int ret;

	mutex_lock(&dts_update_mutex);
	ret = iosf_mbi_read(QRK_MBI_UNIT_RMU, MBI_REG_READ,
			    QRK_DTS_REG_OFFSET_TEMP, &out);
	mutex_unlock(&dts_update_mutex);

	if (ret)
		return ret;

	/*
	 * Thermal Sensor Temperature Register has 8-bit field
	 * for temperature value (offset by temperature base
	 * 50 degree Celsius).
	 */
	out = (out >> QRK_DTS_OFFSET_TEMP) & QRK_DTS_MASK_TEMP;
	*temp = out - QRK_DTS_TEMP_BASE;

	return 0;
}
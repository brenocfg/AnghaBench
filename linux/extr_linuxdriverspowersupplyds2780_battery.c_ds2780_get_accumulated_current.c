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
typedef  int u8 ;
struct ds2780_device_info {int /*<<< orphan*/  dev; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DS2780_ACR_MSB_REG ; 
 int DS2780_CHARGE_UNITS ; 
 int /*<<< orphan*/  DS2780_RSNSP_REG ; 
 int ENXIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ds2780_read16 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 
 int ds2780_read8 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_get_accumulated_current(struct ds2780_device_info *dev_info,
	int *accumulated_current)
{
	int ret, sense_res;
	s16 current_raw;
	u8 sense_res_raw;

	/*
	 * The units of measurement for accumulated current are dependent on
	 * the value of the sense resistor.
	 */
	ret = ds2780_read8(dev_info, &sense_res_raw, DS2780_RSNSP_REG);
	if (ret < 0)
		return ret;

	if (sense_res_raw == 0) {
		dev_err(dev_info->dev, "sense resistor value is 0\n");
		return -ENXIO;
	}
	sense_res = 1000 / sense_res_raw;

	/*
	 * The ACR value is located in 16 bits across the ACR MSB and
	 * LSB registers
	 * Bits 15 - 8 of the ACR value are in bits 7 - 0 of the ACR
	 * MSB register
	 * Bits 7 - 0 of the ACR value are in bits 7 - 0 of the ACR
	 * LSB register
	 */
	ret = ds2780_read16(dev_info, &current_raw, DS2780_ACR_MSB_REG);
	if (ret < 0)
		return ret;

	*accumulated_current = current_raw * (DS2780_CHARGE_UNITS / sense_res);
	return 0;
}
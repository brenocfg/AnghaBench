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
struct pm860x_battery_info {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OCV_MODE_ACTIVE 129 
#define  OCV_MODE_SLEEP 128 
 int /*<<< orphan*/  PM8607_LDO5 ; 
 int /*<<< orphan*/  PM8607_VBAT_MEAS1 ; 
 int measure_12bit_voltage (struct pm860x_battery_info*,int /*<<< orphan*/ ,int*) ; 
 int pm860x_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 

__attribute__((used)) static int measure_vbatt(struct pm860x_battery_info *info, int state,
			 int *data)
{
	unsigned char buf[5];
	int ret;

	switch (state) {
	case OCV_MODE_ACTIVE:
		ret = measure_12bit_voltage(info, PM8607_VBAT_MEAS1, data);
		if (ret)
			return ret;
		/* V_BATT_MEAS(mV) = value * 3 * 1.8 * 1000 / (2^12) */
		*data *= 3;
		break;
	case OCV_MODE_SLEEP:
		/*
		 * voltage value of VBATT in sleep mode is saved in different
		 * registers.
		 * bit[11:10] -- bit[7:6] of LDO9(0x18)
		 * bit[9:8] -- bit[7:6] of LDO8(0x17)
		 * bit[7:6] -- bit[7:6] of LDO7(0x16)
		 * bit[5:4] -- bit[7:6] of LDO6(0x15)
		 * bit[3:0] -- bit[7:4] of LDO5(0x14)
		 */
		ret = pm860x_bulk_read(info->i2c, PM8607_LDO5, 5, buf);
		if (ret < 0)
			return ret;
		ret = ((buf[4] >> 6) << 10) | ((buf[3] >> 6) << 8)
		    | ((buf[2] >> 6) << 6) | ((buf[1] >> 6) << 4)
		    | (buf[0] >> 4);
		/* V_BATT_MEAS(mV) = data * 3 * 1.8 * 1000 / (2^12) */
		*data = ((*data & 0xff) * 27 * 25) >> 9;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}
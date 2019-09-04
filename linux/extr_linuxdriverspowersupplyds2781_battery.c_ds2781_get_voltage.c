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
typedef  int /*<<< orphan*/  u8 ;
struct ds2781_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2781_VOLT_MSB ; 
 int w1_ds2781_read (struct ds2781_device_info*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds2781_get_voltage(struct ds2781_device_info *dev_info,
	int *voltage_uV)
{
	int ret;
	char val[2];
	int voltage_raw;

	ret = w1_ds2781_read(dev_info, val, DS2781_VOLT_MSB, 2 * sizeof(u8));
	if (ret < 0)
		return ret;
	/*
	 * The voltage value is located in 10 bits across the voltage MSB
	 * and LSB registers in two's compliment form
	 * Sign bit of the voltage value is in bit 7 of the voltage MSB register
	 * Bits 9 - 3 of the voltage value are in bits 6 - 0 of the
	 * voltage MSB register
	 * Bits 2 - 0 of the voltage value are in bits 7 - 5 of the
	 * voltage LSB register
	 */
	voltage_raw = (val[0] << 3) |
		(val[1] >> 5);

	/* DS2781 reports voltage in units of 9.76mV, but the battery class
	 * reports in units of uV, so convert by multiplying by 9760. */
	*voltage_uV = voltage_raw * 9760;

	return 0;
}
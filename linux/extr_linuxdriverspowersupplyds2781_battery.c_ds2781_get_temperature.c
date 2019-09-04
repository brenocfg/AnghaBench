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
 int /*<<< orphan*/  DS2781_TEMP_MSB ; 
 int w1_ds2781_read (struct ds2781_device_info*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds2781_get_temperature(struct ds2781_device_info *dev_info,
	int *temp)
{
	int ret;
	char val[2];
	int temp_raw;

	ret = w1_ds2781_read(dev_info, val, DS2781_TEMP_MSB, 2 * sizeof(u8));
	if (ret < 0)
		return ret;
	/*
	 * The temperature value is located in 10 bits across the temperature
	 * MSB and LSB registers in two's compliment form
	 * Sign bit of the temperature value is in bit 7 of the temperature
	 * MSB register
	 * Bits 9 - 3 of the temperature value are in bits 6 - 0 of the
	 * temperature MSB register
	 * Bits 2 - 0 of the temperature value are in bits 7 - 5 of the
	 * temperature LSB register
	 */
	temp_raw = ((val[0]) << 3) |
		(val[1] >> 5);
	*temp = temp_raw + (temp_raw / 4);

	return 0;
}
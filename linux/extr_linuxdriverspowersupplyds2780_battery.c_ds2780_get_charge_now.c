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
typedef  int u16 ;
struct ds2780_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2780_RAAC_MSB_REG ; 
 int ds2780_read16 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_get_charge_now(struct ds2780_device_info *dev_info,
	int *charge_now)
{
	int ret;
	u16 charge_raw;

	/*
	 * The RAAC value is located in 16 bits across the RAAC MSB and
	 * LSB registers
	 * Bits 15 - 8 of the RAAC value are in bits 7 - 0 of the RAAC
	 * MSB register
	 * Bits 7 - 0 of the RAAC value are in bits 7 - 0 of the RAAC
	 * LSB register
	 */
	ret = ds2780_read16(dev_info, &charge_raw, DS2780_RAAC_MSB_REG);
	if (ret < 0)
		return ret;

	*charge_now = charge_raw * 1600;
	return 0;
}
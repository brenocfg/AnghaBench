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
typedef  int u16 ;
struct ds2780_device_info {int dummy; } ;
typedef  int /*<<< orphan*/  raw ;

/* Variables and functions */
 int /*<<< orphan*/  DS2780_RSGAIN_MSB_REG ; 
 int ds2780_save_eeprom (struct ds2780_device_info*,int /*<<< orphan*/ ) ; 
 int ds2780_write (struct ds2780_device_info*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds2780_set_rsgain_register(struct ds2780_device_info *dev_info,
	u16 rsgain)
{
	int ret;
	u8 raw[] = {rsgain >> 8, rsgain & 0xFF};

	ret = ds2780_write(dev_info, raw,
				DS2780_RSGAIN_MSB_REG, sizeof(raw));
	if (ret < 0)
		return ret;

	return ds2780_save_eeprom(dev_info, DS2780_RSGAIN_MSB_REG);
}
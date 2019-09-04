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
struct ds2781_device_info {int dummy; } ;
typedef  int /*<<< orphan*/  raw ;

/* Variables and functions */
 int /*<<< orphan*/  DS2781_RSGAIN_MSB ; 
 int ds2781_save_eeprom (struct ds2781_device_info*,int /*<<< orphan*/ ) ; 
 int ds2781_write (struct ds2781_device_info*,int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds2781_set_rsgain_register(struct ds2781_device_info *dev_info,
	u16 rsgain)
{
	int ret;
	u8 raw[] = {rsgain >> 8, rsgain & 0xFF};

	ret = ds2781_write(dev_info, raw,
				DS2781_RSGAIN_MSB, sizeof(raw));
	if (ret < 0)
		return ret;

	return ds2781_save_eeprom(dev_info, DS2781_RSGAIN_MSB);
}
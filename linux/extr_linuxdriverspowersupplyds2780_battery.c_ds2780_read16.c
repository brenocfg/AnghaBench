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
struct ds2780_device_info {int dummy; } ;
typedef  int s16 ;
typedef  int /*<<< orphan*/  raw ;

/* Variables and functions */
 int ds2780_battery_io (struct ds2780_device_info*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_read16(struct ds2780_device_info *dev_info, s16 *val,
	int addr)
{
	int ret;
	u8 raw[2];

	ret = ds2780_battery_io(dev_info, raw, addr, sizeof(raw), 0);
	if (ret < 0)
		return ret;

	*val = (raw[0] << 8) | raw[1];

	return 0;
}
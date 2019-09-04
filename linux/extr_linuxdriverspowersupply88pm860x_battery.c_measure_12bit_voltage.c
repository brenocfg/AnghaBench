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
 int pm860x_bulk_read (int /*<<< orphan*/ ,int,int,unsigned char*) ; 

__attribute__((used)) static int measure_12bit_voltage(struct pm860x_battery_info *info,
				 int offset, int *data)
{
	unsigned char buf[2];
	int ret;

	ret = pm860x_bulk_read(info->i2c, offset, 2, buf);
	if (ret < 0)
		return ret;

	*data = ((buf[0] & 0xff) << 4) | (buf[1] & 0x0f);
	/* V_MEAS(mV) = data * 1.8 * 1000 / (2^12) */
	*data = ((*data & 0xfff) * 9 * 25) >> 9;
	return 0;
}
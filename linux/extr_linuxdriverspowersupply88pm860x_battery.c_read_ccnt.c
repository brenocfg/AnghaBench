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
 int /*<<< orphan*/  PM8607_CCNT ; 
 int /*<<< orphan*/  PM8607_CCNT_MEAS1 ; 
 int pm860x_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int read_ccnt(struct pm860x_battery_info *info, int offset,
		     int *ccnt)
{
	unsigned char buf[2];
	int ret;

	ret = pm860x_set_bits(info->i2c, PM8607_CCNT, 7, offset & 7);
	if (ret < 0)
		goto out;
	ret = pm860x_bulk_read(info->i2c, PM8607_CCNT_MEAS1, 2, buf);
	if (ret < 0)
		goto out;
	*ccnt = ((buf[0] & 0xff) << 8) | (buf[1] & 0xff);
	return 0;
out:
	return ret;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {int dummy; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1374_REG_TOD0 ; 
 int ds1374_read_rtc (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ds1374_read_time(struct device *dev, struct rtc_time *time)
{
	struct i2c_client *client = to_i2c_client(dev);
	u32 itime;
	int ret;

	ret = ds1374_read_rtc(client, &itime, DS1374_REG_TOD0, 4);
	if (!ret)
		rtc_time_to_tm(itime, time);

	return ret;
}
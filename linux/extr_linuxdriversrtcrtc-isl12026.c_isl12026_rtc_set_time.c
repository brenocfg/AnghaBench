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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int EIO ; 
 int ISL12026_REG_HR_MIL ; 
 int ISL12026_REG_SC ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int isl12026_arm_write (struct i2c_client*) ; 
 int isl12026_disarm_write (struct i2c_client*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int isl12026_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret;
	u8 op[10];
	struct i2c_msg msg = {
		.addr	= client->addr,
		.flags	= 0,
		.len	= sizeof(op),
		.buf	= op
	};

	ret = isl12026_arm_write(client);
	if (ret)
		return ret;

	/* Set the CCR registers */
	op[0] = 0;
	op[1] = ISL12026_REG_SC;
	op[2] = bin2bcd(tm->tm_sec); /* SC */
	op[3] = bin2bcd(tm->tm_min); /* MN */
	op[4] = bin2bcd(tm->tm_hour) | ISL12026_REG_HR_MIL; /* HR */
	op[5] = bin2bcd(tm->tm_mday); /* DT */
	op[6] = bin2bcd(tm->tm_mon + 1); /* MO */
	op[7] = bin2bcd(tm->tm_year % 100); /* YR */
	op[8] = bin2bcd(tm->tm_wday & 7); /* DW */
	op[9] = bin2bcd(tm->tm_year >= 100 ? 20 : 19); /* Y2K */
	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret != 1) {
		dev_err(&client->dev, "write error CCR, ret=%d\n", ret);
		ret = ret < 0 ? ret : -EIO;
		goto out;
	}

	ret = isl12026_disarm_write(client);
out:
	return ret;
}
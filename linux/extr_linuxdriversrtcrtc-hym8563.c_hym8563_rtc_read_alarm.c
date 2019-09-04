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
struct rtc_time {int tm_min; int tm_hour; int tm_mday; int tm_wday; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HYM8563_ALM_BIT_DISABLE ; 
 int /*<<< orphan*/  HYM8563_ALM_MIN ; 
 int /*<<< orphan*/  HYM8563_CTL2 ; 
 int HYM8563_CTL2_AIE ; 
 int HYM8563_DAY_MASK ; 
 int HYM8563_HOUR_MASK ; 
 int HYM8563_MIN_MASK ; 
 int HYM8563_WEEKDAY_MASK ; 
 int bcd2bin (int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int hym8563_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rtc_time *alm_tm = &alm->time;
	u8 buf[4];
	int ret;

	ret = i2c_smbus_read_i2c_block_data(client, HYM8563_ALM_MIN, 4, buf);
	if (ret < 0)
		return ret;

	/* The alarm only has a minute accuracy */
	alm_tm->tm_sec = 0;

	alm_tm->tm_min = (buf[0] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[0] & HYM8563_MIN_MASK);
	alm_tm->tm_hour = (buf[1] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[1] & HYM8563_HOUR_MASK);
	alm_tm->tm_mday = (buf[2] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[2] & HYM8563_DAY_MASK);
	alm_tm->tm_wday = (buf[3] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[3] & HYM8563_WEEKDAY_MASK);

	ret = i2c_smbus_read_byte_data(client, HYM8563_CTL2);
	if (ret < 0)
		return ret;

	if (ret & HYM8563_CTL2_AIE)
		alm->enabled = 1;

	return 0;
}
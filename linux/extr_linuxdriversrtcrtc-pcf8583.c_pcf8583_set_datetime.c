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
struct rtc_time {int tm_year; int tm_wday; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int bin2bcd (scalar_t__) ; 
 int get_ctrl (struct i2c_client*) ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int pcf8583_set_datetime(struct i2c_client *client, struct rtc_time *dt, int datetoo)
{
	unsigned char buf[8];
	int ret, len = 6;

	buf[0] = 0;
	buf[1] = get_ctrl(client) | 0x80;
	buf[2] = 0;
	buf[3] = bin2bcd(dt->tm_sec);
	buf[4] = bin2bcd(dt->tm_min);
	buf[5] = bin2bcd(dt->tm_hour);

	if (datetoo) {
		len = 8;
		buf[6] = bin2bcd(dt->tm_mday) | (dt->tm_year << 6);
		buf[7] = bin2bcd(dt->tm_mon + 1)  | (dt->tm_wday << 5);
	}

	ret = i2c_master_send(client, (char *)buf, len);
	if (ret != len)
		return -EIO;

	buf[1] = get_ctrl(client);
	ret = i2c_master_send(client, (char *)buf, 2);

	return ret == 2 ? 0 : -EIO;
}
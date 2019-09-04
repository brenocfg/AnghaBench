#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_mon; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int M41T80_ALMON_AFE ; 
 int M41T80_ALMON_SQWE ; 
 int M41T80_FLAGS_AF ; 
 int /*<<< orphan*/  M41T80_REG_ALARM_MON ; 
 int /*<<< orphan*/  M41T80_REG_FLAGS ; 
 int bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int m41t80_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 alarmvals[5];
	int ret, err;

	alarmvals[0] = bin2bcd(alrm->time.tm_mon + 1);
	alarmvals[1] = bin2bcd(alrm->time.tm_mday);
	alarmvals[2] = bin2bcd(alrm->time.tm_hour);
	alarmvals[3] = bin2bcd(alrm->time.tm_min);
	alarmvals[4] = bin2bcd(alrm->time.tm_sec);

	/* Clear AF and AFE flags */
	ret = i2c_smbus_read_byte_data(client, M41T80_REG_ALARM_MON);
	if (ret < 0)
		return ret;
	err = i2c_smbus_write_byte_data(client, M41T80_REG_ALARM_MON,
					ret & ~(M41T80_ALMON_AFE));
	if (err < 0) {
		dev_err(dev, "Unable to clear AFE bit\n");
		return err;
	}

	/* Keep SQWE bit value */
	alarmvals[0] |= (ret & M41T80_ALMON_SQWE);

	ret = i2c_smbus_read_byte_data(client, M41T80_REG_FLAGS);
	if (ret < 0)
		return ret;

	err = i2c_smbus_write_byte_data(client, M41T80_REG_FLAGS,
					ret & ~(M41T80_FLAGS_AF));
	if (err < 0) {
		dev_err(dev, "Unable to clear AF bit\n");
		return err;
	}

	/* Write the alarm */
	err = i2c_smbus_write_i2c_block_data(client, M41T80_REG_ALARM_MON,
					     5, alarmvals);
	if (err)
		return err;

	/* Enable the alarm interrupt */
	if (alrm->enabled) {
		alarmvals[0] |= M41T80_ALMON_AFE;
		err = i2c_smbus_write_byte_data(client, M41T80_REG_ALARM_MON,
						alarmvals[0]);
		if (err)
			return err;
	}

	return 0;
}
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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  regs ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCF85063_REG_SC ; 
 int bin2bcd (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 int pcf85063_start_clock (struct i2c_client*,int) ; 
 int pcf85063_stop_clock (struct i2c_client*,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int pcf85063_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	int rc;
	u8 regs[7];
	u8 ctrl1;

	if ((tm->tm_year < 100) || (tm->tm_year > 199))
		return -EINVAL;

	/*
	 * to accurately set the time, reset the divider chain and keep it in
	 * reset state until all time/date registers are written
	 */
	rc = pcf85063_stop_clock(client, &ctrl1);
	if (rc != 0)
		return rc;

	/* hours, minutes and seconds */
	regs[0] = bin2bcd(tm->tm_sec) & 0x7F; /* clear OS flag */

	regs[1] = bin2bcd(tm->tm_min);
	regs[2] = bin2bcd(tm->tm_hour);

	/* Day of month, 1 - 31 */
	regs[3] = bin2bcd(tm->tm_mday);

	/* Day, 0 - 6 */
	regs[4] = tm->tm_wday & 0x07;

	/* month, 1 - 12 */
	regs[5] = bin2bcd(tm->tm_mon + 1);

	/* year and century */
	regs[6] = bin2bcd(tm->tm_year - 100);

	/* write all registers at once */
	rc = i2c_smbus_write_i2c_block_data(client, PCF85063_REG_SC,
					    sizeof(regs), regs);
	if (rc < 0) {
		dev_err(&client->dev, "date/time register write error\n");
		return rc;
	}

	/*
	 * Write the control register as a separate action since the size of
	 * the register space is different between the PCF85063TP and
	 * PCF85063A devices.  The rollover point can not be used.
	 */
	rc = pcf85063_start_clock(client, ctrl1);
	if (rc != 0)
		return rc;

	return 0;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_wday; int tm_year; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t MAX6900_REG_CENTURY ; 
 size_t MAX6900_REG_CT ; 
 int /*<<< orphan*/  MAX6900_REG_CT_WP ; 
 size_t MAX6900_REG_DT ; 
 size_t MAX6900_REG_DW ; 
 size_t MAX6900_REG_HR ; 
 int MAX6900_REG_LEN ; 
 size_t MAX6900_REG_MN ; 
 size_t MAX6900_REG_MO ; 
 size_t MAX6900_REG_SC ; 
 size_t MAX6900_REG_YR ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int max6900_i2c_clear_write_protect (struct i2c_client*) ; 
 int max6900_i2c_write_regs (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int max6900_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 regs[MAX6900_REG_LEN];
	int rc;

	rc = max6900_i2c_clear_write_protect(client);
	if (rc < 0)
		return rc;

	regs[MAX6900_REG_SC] = bin2bcd(tm->tm_sec);
	regs[MAX6900_REG_MN] = bin2bcd(tm->tm_min);
	regs[MAX6900_REG_HR] = bin2bcd(tm->tm_hour);
	regs[MAX6900_REG_DT] = bin2bcd(tm->tm_mday);
	regs[MAX6900_REG_MO] = bin2bcd(tm->tm_mon + 1);
	regs[MAX6900_REG_DW] = bin2bcd(tm->tm_wday);
	regs[MAX6900_REG_YR] = bin2bcd(tm->tm_year % 100);
	regs[MAX6900_REG_CENTURY] = bin2bcd((tm->tm_year + 1900) / 100);
	/* set write protect */
	regs[MAX6900_REG_CT] = MAX6900_REG_CT_WP;

	rc = max6900_i2c_write_regs(client, regs);
	if (rc < 0)
		return rc;

	return 0;
}
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
struct rv8803_data {int ctrl; struct i2c_client* client; } ;
struct TYPE_2__ {void* tm_mday; void* tm_hour; void* tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV8803_ALARM_MIN ; 
 int RV8803_CTRL_AIE ; 
 int /*<<< orphan*/  RV8803_FLAG ; 
 int RV8803_FLAG_AF ; 
 void* bcd2bin (int) ; 
 struct rv8803_data* dev_get_drvdata (struct device*) ; 
 int rv8803_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int rv8803_read_regs (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int rv8803_get_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct rv8803_data *rv8803 = dev_get_drvdata(dev);
	struct i2c_client *client = rv8803->client;
	u8 alarmvals[3];
	int flags, ret;

	ret = rv8803_read_regs(client, RV8803_ALARM_MIN, 3, alarmvals);
	if (ret)
		return ret;

	flags = rv8803_read_reg(client, RV8803_FLAG);
	if (flags < 0)
		return flags;

	alrm->time.tm_sec  = 0;
	alrm->time.tm_min  = bcd2bin(alarmvals[0] & 0x7f);
	alrm->time.tm_hour = bcd2bin(alarmvals[1] & 0x3f);
	alrm->time.tm_mday = bcd2bin(alarmvals[2] & 0x3f);

	alrm->enabled = !!(rv8803->ctrl & RV8803_CTRL_AIE);
	alrm->pending = (flags & RV8803_FLAG_AF) && alrm->enabled;

	return 0;
}
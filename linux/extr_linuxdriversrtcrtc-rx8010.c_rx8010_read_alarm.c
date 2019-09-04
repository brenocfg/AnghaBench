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
struct rx8010_data {int ctrlreg; struct i2c_client* client; } ;
struct TYPE_2__ {void* tm_mday; void* tm_hour; void* tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int RX8010_ALARM_AE ; 
 int /*<<< orphan*/  RX8010_ALMIN ; 
 int RX8010_CTRL_AIE ; 
 int /*<<< orphan*/  RX8010_FLAG ; 
 int RX8010_FLAG_AF ; 
 void* bcd2bin (int) ; 
 struct rx8010_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int rx8010_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct rx8010_data *rx8010 = dev_get_drvdata(dev);
	struct i2c_client *client = rx8010->client;
	u8 alarmvals[3];
	int flagreg;
	int err;

	err = i2c_smbus_read_i2c_block_data(client, RX8010_ALMIN, 3, alarmvals);
	if (err != 3)
		return err < 0 ? err : -EIO;

	flagreg = i2c_smbus_read_byte_data(client, RX8010_FLAG);
	if (flagreg < 0)
		return flagreg;

	t->time.tm_sec = 0;
	t->time.tm_min = bcd2bin(alarmvals[0] & 0x7f);
	t->time.tm_hour = bcd2bin(alarmvals[1] & 0x3f);

	if (!(alarmvals[2] & RX8010_ALARM_AE))
		t->time.tm_mday = bcd2bin(alarmvals[2] & 0x7f);

	t->enabled = !!(rx8010->ctrlreg & RX8010_CTRL_AIE);
	t->pending = (flagreg & RX8010_FLAG_AF) && t->enabled;

	return 0;
}
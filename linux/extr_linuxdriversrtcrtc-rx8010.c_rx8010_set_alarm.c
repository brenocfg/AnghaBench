#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rx8010_data {int ctrlreg; int /*<<< orphan*/  client; TYPE_4__* rtc; } ;
struct TYPE_5__ {int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {scalar_t__ enabled; } ;
struct TYPE_6__ {scalar_t__ enabled; } ;
struct TYPE_8__ {TYPE_3__ aie_timer; TYPE_2__ uie_rtctimer; } ;

/* Variables and functions */
 int RX8010_ALARM_AE ; 
 int /*<<< orphan*/  RX8010_ALMIN ; 
 int /*<<< orphan*/  RX8010_ALWDAY ; 
 int /*<<< orphan*/  RX8010_CTRL ; 
 int RX8010_CTRL_AIE ; 
 int RX8010_CTRL_UIE ; 
 int /*<<< orphan*/  RX8010_EXT ; 
 int RX8010_EXT_WADA ; 
 int /*<<< orphan*/  RX8010_FLAG ; 
 int RX8010_FLAG_AF ; 
 int bin2bcd (int /*<<< orphan*/ ) ; 
 struct rx8010_data* dev_get_drvdata (struct device*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_write_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rx8010_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	int extreg, flagreg;
	int err;

	flagreg = i2c_smbus_read_byte_data(client, RX8010_FLAG);
	if (flagreg < 0) {
		return flagreg;
	}

	if (rx8010->ctrlreg & (RX8010_CTRL_AIE | RX8010_CTRL_UIE)) {
		rx8010->ctrlreg &= ~(RX8010_CTRL_AIE | RX8010_CTRL_UIE);
		err = i2c_smbus_write_byte_data(rx8010->client, RX8010_CTRL,
						rx8010->ctrlreg);
		if (err < 0) {
			return err;
		}
	}

	flagreg &= ~RX8010_FLAG_AF;
	err = i2c_smbus_write_byte_data(rx8010->client, RX8010_FLAG, flagreg);
	if (err < 0)
		return err;

	alarmvals[0] = bin2bcd(t->time.tm_min);
	alarmvals[1] = bin2bcd(t->time.tm_hour);
	alarmvals[2] = bin2bcd(t->time.tm_mday);

	err = i2c_smbus_write_i2c_block_data(rx8010->client, RX8010_ALMIN,
					     2, alarmvals);
	if (err < 0)
		return err;

	extreg = i2c_smbus_read_byte_data(client, RX8010_EXT);
	if (extreg < 0)
		return extreg;

	extreg |= RX8010_EXT_WADA;
	err = i2c_smbus_write_byte_data(rx8010->client, RX8010_EXT, extreg);
	if (err < 0)
		return err;

	if (alarmvals[2] == 0)
		alarmvals[2] |= RX8010_ALARM_AE;

	err = i2c_smbus_write_byte_data(rx8010->client, RX8010_ALWDAY,
					alarmvals[2]);
	if (err < 0)
		return err;

	if (t->enabled) {
		if (rx8010->rtc->uie_rtctimer.enabled)
			rx8010->ctrlreg |= RX8010_CTRL_UIE;
		if (rx8010->rtc->aie_timer.enabled)
			rx8010->ctrlreg |=
				(RX8010_CTRL_AIE | RX8010_CTRL_UIE);

		err = i2c_smbus_write_byte_data(rx8010->client, RX8010_CTRL,
						rx8010->ctrlreg);
		if (err < 0)
			return err;
	}

	return 0;
}
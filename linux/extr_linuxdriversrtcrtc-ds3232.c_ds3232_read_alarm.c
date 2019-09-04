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
struct TYPE_2__ {void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct ds3232 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_ALARM1 ; 
 int /*<<< orphan*/  DS3232_REG_CR ; 
 int DS3232_REG_CR_A1IE ; 
 int /*<<< orphan*/  DS3232_REG_SR ; 
 int DS3232_REG_SR_A1F ; 
 void* bcd2bin (int) ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ds3232_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	int control, stat;
	int ret;
	u8 buf[4];

	ret = regmap_read(ds3232->regmap, DS3232_REG_SR, &stat);
	if (ret)
		goto out;
	ret = regmap_read(ds3232->regmap, DS3232_REG_CR, &control);
	if (ret)
		goto out;
	ret = regmap_bulk_read(ds3232->regmap, DS3232_REG_ALARM1, buf, 4);
	if (ret)
		goto out;

	alarm->time.tm_sec = bcd2bin(buf[0] & 0x7F);
	alarm->time.tm_min = bcd2bin(buf[1] & 0x7F);
	alarm->time.tm_hour = bcd2bin(buf[2] & 0x7F);
	alarm->time.tm_mday = bcd2bin(buf[3] & 0x7F);

	alarm->enabled = !!(control & DS3232_REG_CR_A1IE);
	alarm->pending = !!(stat & DS3232_REG_SR_A1F);

	ret = 0;
out:
	return ret;
}
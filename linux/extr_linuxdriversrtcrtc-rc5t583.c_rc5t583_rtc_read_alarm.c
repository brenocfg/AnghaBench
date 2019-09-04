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
typedef  int u32 ;
struct TYPE_2__ {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; scalar_t__ tm_sec; } ;
struct rtc_wkalrm {int enabled; TYPE_1__ time; } ;
struct rc5t583 {int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int NUM_YAL_REGS ; 
 int /*<<< orphan*/  RC5T583_RTC_AY_MIN ; 
 int /*<<< orphan*/  RC5T583_RTC_CTL1 ; 
 int SET_YAL ; 
 void* bcd2bin (unsigned char) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rc5t583* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rc5t583_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct rc5t583 *rc5t583 = dev_get_drvdata(dev->parent);
	unsigned char alarm_data[NUM_YAL_REGS];
	u32 interrupt_enable;
	int ret;

	ret = regmap_bulk_read(rc5t583->regmap, RC5T583_RTC_AY_MIN, alarm_data,
		NUM_YAL_REGS);
	if (ret < 0) {
		dev_err(dev, "rtc_read_alarm error %d\n", ret);
		return ret;
	}

	alm->time.tm_sec = 0;
	alm->time.tm_min = bcd2bin(alarm_data[0]);
	alm->time.tm_hour = bcd2bin(alarm_data[1]);
	alm->time.tm_mday = bcd2bin(alarm_data[2]);
	alm->time.tm_mon = bcd2bin(alarm_data[3]) - 1;
	alm->time.tm_year = bcd2bin(alarm_data[4]) + 100;

	ret = regmap_read(rc5t583->regmap, RC5T583_RTC_CTL1, &interrupt_enable);
	if (ret < 0)
		return ret;

	/* check if YALE is set */
	if (interrupt_enable & SET_YAL)
		alm->enabled = 1;

	return ret;
}
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
struct max77686_rtc_info {int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  rtc_regmap; } ;
typedef  enum MAX77686_RTC_OP { ____Placeholder_MAX77686_RTC_OP } MAX77686_RTC_OP ;
struct TYPE_2__ {unsigned long delay; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int MAX77686_RTC_WRITE ; 
 size_t REG_RTC_UPDATE0 ; 
 int RTC_RBUDR_SHIFT ; 
 int RTC_UDR_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int max77686_rtc_update(struct max77686_rtc_info *info,
			       enum MAX77686_RTC_OP op)
{
	int ret;
	unsigned int data;
	unsigned long delay = info->drv_data->delay;

	if (op == MAX77686_RTC_WRITE)
		data = 1 << RTC_UDR_SHIFT;
	else
		data = 1 << RTC_RBUDR_SHIFT;

	ret = regmap_update_bits(info->rtc_regmap,
				 info->drv_data->map[REG_RTC_UPDATE0],
				 data, data);
	if (ret < 0)
		dev_err(info->dev, "Fail to write update reg(ret=%d, data=0x%x)\n",
			ret, data);
	else {
		/* Minimum delay required before RTC update. */
		usleep_range(delay, delay * 2);
	}

	return ret;
}
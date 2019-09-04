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
struct max77686_rtc_info {int rtc_24hr_mode; int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  rtc_regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int BCD_EN_SHIFT ; 
 int /*<<< orphan*/  MAX77686_RTC_WRITE ; 
 int MODEL24_SHIFT ; 
 size_t REG_RTC_CONTROLM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max77686_rtc_update (struct max77686_rtc_info*,int /*<<< orphan*/ ) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77686_rtc_init_reg(struct max77686_rtc_info *info)
{
	u8 data[2];
	int ret;

	/* Set RTC control register : Binary mode, 24hour mdoe */
	data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);
	data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEL24_SHIFT);

	info->rtc_24hr_mode = 1;

	ret = regmap_bulk_write(info->rtc_regmap,
				info->drv_data->map[REG_RTC_CONTROLM],
				data, ARRAY_SIZE(data));
	if (ret < 0) {
		dev_err(info->dev, "Fail to write controlm reg(%d)\n", ret);
		return ret;
	}

	ret = max77686_rtc_update(info, MAX77686_RTC_WRITE);
	return ret;
}
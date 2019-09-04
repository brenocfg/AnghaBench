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
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct max77686_rtc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__* drv_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  rtc_regmap; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int* map; unsigned int const alarm_pending_status_reg; scalar_t__ alarm_enable_reg; } ;

/* Variables and functions */
 int ALARM_ENABLE_MASK ; 
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 unsigned int const MAX77686_INVALID_REG ; 
 int /*<<< orphan*/  MAX77686_RTC_READ ; 
 size_t REG_ALARM1_SEC ; 
 size_t REG_RTC_AE1 ; 
 unsigned int const REG_RTC_NONE ; 
 int RTC_NR_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77686_rtc_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  max77686_rtc_data_to_tm (int*,int /*<<< orphan*/ *,struct max77686_rtc_info*) ; 
 int max77686_rtc_update (struct max77686_rtc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,unsigned int const,int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int const,unsigned int*) ; 

__attribute__((used)) static int max77686_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max77686_rtc_info *info = dev_get_drvdata(dev);
	u8 data[RTC_NR_TIME];
	unsigned int val;
	const unsigned int *map = info->drv_data->map;
	int i, ret;

	mutex_lock(&info->lock);

	ret = max77686_rtc_update(info, MAX77686_RTC_READ);
	if (ret < 0)
		goto out;

	ret = regmap_bulk_read(info->rtc_regmap, map[REG_ALARM1_SEC],
			       data, ARRAY_SIZE(data));
	if (ret < 0) {
		dev_err(info->dev, "Fail to read alarm reg(%d)\n", ret);
		goto out;
	}

	max77686_rtc_data_to_tm(data, &alrm->time, info);

	alrm->enabled = 0;

	if (info->drv_data->alarm_enable_reg) {
		if (map[REG_RTC_AE1] == REG_RTC_NONE) {
			ret = -EINVAL;
			dev_err(info->dev,
				"alarm enable register not set(%d)\n", ret);
			goto out;
		}

		ret = regmap_read(info->rtc_regmap, map[REG_RTC_AE1], &val);
		if (ret < 0) {
			dev_err(info->dev,
				"fail to read alarm enable(%d)\n", ret);
			goto out;
		}

		if (val)
			alrm->enabled = 1;
	} else {
		for (i = 0; i < ARRAY_SIZE(data); i++) {
			if (data[i] & ALARM_ENABLE_MASK) {
				alrm->enabled = 1;
				break;
			}
		}
	}

	alrm->pending = 0;

	if (info->drv_data->alarm_pending_status_reg == MAX77686_INVALID_REG)
		goto out;

	ret = regmap_read(info->regmap,
			  info->drv_data->alarm_pending_status_reg, &val);
	if (ret < 0) {
		dev_err(info->dev,
			"Fail to read alarm pending status reg(%d)\n", ret);
		goto out;
	}

	if (val & (1 << 4)) /* RTCA1 */
		alrm->pending = 1;

out:
	mutex_unlock(&info->lock);
	return ret;
}
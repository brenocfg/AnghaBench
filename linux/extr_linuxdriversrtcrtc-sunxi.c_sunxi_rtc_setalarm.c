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
typedef  int u32 ;
typedef  int time64_t ;
struct sunxi_rtc_dev {scalar_t__ base; } ;
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEC_IN_DAY ; 
 unsigned long SEC_IN_HOUR ; 
 unsigned long SEC_IN_MIN ; 
 scalar_t__ SUNXI_ALRM_DHMS ; 
 scalar_t__ SUNXI_ALRM_IRQ_EN ; 
 int SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN ; 
 int SUNXI_ALRM_SET_DAY_VALUE (unsigned long) ; 
 int SUNXI_ALRM_SET_HOUR_VALUE (unsigned long) ; 
 int SUNXI_ALRM_SET_MIN_VALUE (unsigned long) ; 
 int SUNXI_ALRM_SET_SEC_VALUE (unsigned long) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sunxi_rtc_dev* dev_get_drvdata (struct device*) ; 
 int rtc_tm_sub (struct rtc_time*,struct rtc_time*) ; 
 int sunxi_rtc_gettime (struct device*,struct rtc_time*) ; 
 int /*<<< orphan*/  sunxi_rtc_setaie (int /*<<< orphan*/ ,struct sunxi_rtc_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sunxi_rtc_setalarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	struct rtc_time *alrm_tm = &wkalrm->time;
	struct rtc_time tm_now;
	u32 alrm;
	time64_t diff;
	unsigned long time_gap;
	unsigned long time_gap_day;
	unsigned long time_gap_hour;
	unsigned long time_gap_min;
	int ret;

	ret = sunxi_rtc_gettime(dev, &tm_now);
	if (ret < 0) {
		dev_err(dev, "Error in getting time\n");
		return -EINVAL;
	}

	diff = rtc_tm_sub(alrm_tm, &tm_now);
	if (diff <= 0) {
		dev_err(dev, "Date to set in the past\n");
		return -EINVAL;
	}

	if (diff > 255 * SEC_IN_DAY) {
		dev_err(dev, "Day must be in the range 0 - 255\n");
		return -EINVAL;
	}

	time_gap = diff;
	time_gap_day = time_gap / SEC_IN_DAY;
	time_gap -= time_gap_day * SEC_IN_DAY;
	time_gap_hour = time_gap / SEC_IN_HOUR;
	time_gap -= time_gap_hour * SEC_IN_HOUR;
	time_gap_min = time_gap / SEC_IN_MIN;
	time_gap -= time_gap_min * SEC_IN_MIN;

	sunxi_rtc_setaie(0, chip);
	writel(0, chip->base + SUNXI_ALRM_DHMS);
	usleep_range(100, 300);

	alrm = SUNXI_ALRM_SET_SEC_VALUE(time_gap) |
		SUNXI_ALRM_SET_MIN_VALUE(time_gap_min) |
		SUNXI_ALRM_SET_HOUR_VALUE(time_gap_hour) |
		SUNXI_ALRM_SET_DAY_VALUE(time_gap_day);
	writel(alrm, chip->base + SUNXI_ALRM_DHMS);

	writel(0, chip->base + SUNXI_ALRM_IRQ_EN);
	writel(SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN, chip->base + SUNXI_ALRM_IRQ_EN);

	sunxi_rtc_setaie(wkalrm->enabled, chip);

	return 0;
}
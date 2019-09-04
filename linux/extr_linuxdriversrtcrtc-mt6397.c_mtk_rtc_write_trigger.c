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
struct mt6397_rtc {scalar_t__ addr_base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 scalar_t__ RTC_BBPU ; 
 int RTC_BBPU_CBUSY ; 
 scalar_t__ RTC_WRTGR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mtk_rtc_write_trigger(struct mt6397_rtc *rtc)
{
	unsigned long timeout = jiffies + HZ;
	int ret;
	u32 data;

	ret = regmap_write(rtc->regmap, rtc->addr_base + RTC_WRTGR, 1);
	if (ret < 0)
		return ret;

	while (1) {
		ret = regmap_read(rtc->regmap, rtc->addr_base + RTC_BBPU,
				  &data);
		if (ret < 0)
			break;
		if (!(data & RTC_BBPU_CBUSY))
			break;
		if (time_after(jiffies, timeout)) {
			ret = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}

	return ret;
}
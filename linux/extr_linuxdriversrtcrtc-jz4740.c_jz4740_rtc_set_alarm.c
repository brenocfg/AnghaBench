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
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct jz4740_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_RTC_SEC_ALARM ; 
 int JZ_RTC_CTRL_AE ; 
 int JZ_RTC_CTRL_AF_IRQ ; 
 struct jz4740_rtc* dev_get_drvdata (struct device*) ; 
 int jz4740_rtc_ctrl_set_bits (struct jz4740_rtc*,int,int /*<<< orphan*/ ) ; 
 int jz4740_rtc_reg_write (struct jz4740_rtc*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static int jz4740_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	int ret;
	struct jz4740_rtc *rtc = dev_get_drvdata(dev);
	unsigned long secs;

	rtc_tm_to_time(&alrm->time, &secs);

	ret = jz4740_rtc_reg_write(rtc, JZ_REG_RTC_SEC_ALARM, secs);
	if (!ret)
		ret = jz4740_rtc_ctrl_set_bits(rtc,
			JZ_RTC_CTRL_AE | JZ_RTC_CTRL_AF_IRQ, alrm->enabled);

	return ret;
}
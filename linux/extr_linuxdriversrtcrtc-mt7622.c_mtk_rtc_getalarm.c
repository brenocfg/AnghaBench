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
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int enabled; int pending; struct rtc_time time; } ;
struct mtk_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_AL ; 
 int /*<<< orphan*/  MTK_RTC_AL_CTL ; 
 int /*<<< orphan*/  MTK_RTC_INT ; 
 int RTC_AL_EN ; 
 int RTC_INT_AL_STA ; 
 struct mtk_rtc* dev_get_drvdata (struct device*) ; 
 int mtk_r32 (struct mtk_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_rtc_get_alarm_or_time (struct mtk_rtc*,struct rtc_time*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_rtc_getalarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	struct mtk_rtc *hw = dev_get_drvdata(dev);
	struct rtc_time *alrm_tm = &wkalrm->time;

	mtk_rtc_get_alarm_or_time(hw, alrm_tm, MTK_AL);

	wkalrm->enabled = !!(mtk_r32(hw, MTK_RTC_AL_CTL) & RTC_AL_EN);
	wkalrm->pending = !!(mtk_r32(hw, MTK_RTC_INT) & RTC_INT_AL_STA);

	return 0;
}
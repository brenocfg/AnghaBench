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
typedef  scalar_t__ u32 ;
struct rtc_time {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_mday; scalar_t__ tm_wday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; } ;
struct mtk_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_DOM ; 
 int /*<<< orphan*/  MTK_DOW ; 
 int /*<<< orphan*/  MTK_HOU ; 
 int /*<<< orphan*/  MTK_MIN ; 
 int /*<<< orphan*/  MTK_MON ; 
 scalar_t__ MTK_RTC_TM_YR_OFFSET ; 
 int /*<<< orphan*/  MTK_RTC_TREG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_SEC ; 
 int /*<<< orphan*/  MTK_YEA ; 
 scalar_t__ mtk_r32 (struct mtk_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_rtc_get_alarm_or_time(struct mtk_rtc *hw, struct rtc_time *tm,
				      int time_alarm)
{
	u32 year, mon, mday, wday, hour, min, sec;

	/*
	 * Read again until the field of the second is not changed which
	 * ensures all fields in the consistent state. Note that MTK_SEC must
	 * be read first. In this way, it guarantees the others remain not
	 * changed when the results for two MTK_SEC consecutive reads are same.
	 */
	do {
		sec = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_SEC));
		min = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_MIN));
		hour = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_HOU));
		wday = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_DOW));
		mday = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_DOM));
		mon = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_MON));
		year = mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_YEA));
	} while (sec != mtk_r32(hw, MTK_RTC_TREG(time_alarm, MTK_SEC)));

	tm->tm_sec  = sec;
	tm->tm_min  = min;
	tm->tm_hour = hour;
	tm->tm_wday = wday;
	tm->tm_mday = mday;
	tm->tm_mon  = mon - 1;

	/* Rebase to the absolute year which userspace queries */
	tm->tm_year = year + MTK_RTC_TM_YR_OFFSET;
}
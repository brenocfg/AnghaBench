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
typedef  int uint32_t ;
typedef  scalar_t__ time_t ;
struct tm {int tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct rtc_timeval {scalar_t__ tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cron_handle_time (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cron_timer ; 
 int /*<<< orphan*/  gmtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  os_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtctime_gettimeofday (struct rtc_timeval*) ; 

__attribute__((used)) static void cron_handle_tmr() {
  struct rtc_timeval tv;
  rtctime_gettimeofday(&tv);
  if (tv.tv_sec == 0) { // Wait for RTC time
    os_timer_arm(&cron_timer, 1000, 0);
    return;
  }
  time_t t = tv.tv_sec;
  struct tm tm;
  gmtime_r(&t, &tm);
  uint32_t diff = 60000 - tm.tm_sec * 1000 - tv.tv_usec / 1000;
  if (tm.tm_sec == 59) {
    t++;
    diff += 60000;
    gmtime_r(&t, &tm);
  }
  os_timer_arm(&cron_timer, diff, 0);
  cron_handle_time(tm.tm_mon + 1, tm.tm_mday, tm.tm_wday, tm.tm_hour, tm.tm_min);
}
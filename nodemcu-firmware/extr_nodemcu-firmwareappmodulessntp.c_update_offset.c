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

/* Variables and functions */

__attribute__((used)) static void update_offset()
{
  // This may insert or remove an offset second -- i.e. a leap second
  // This can only happen if it is at midnight UTC.
#ifdef LUA_USE_MODULES_RTCTIME
  struct rtc_timeval tv;

  if (pending_LI && using_offset) {
    rtctime_gettimeofday (&tv);
    sntp_dbg("Now=%d, next=%d\n", tv.tv_sec - the_offset, next_midnight);
    if (next_midnight < 100000) {
      next_midnight = get_next_midnight(tv.tv_sec);
    } else if (tv.tv_sec - the_offset >= next_midnight) {
      next_midnight = get_next_midnight(tv.tv_sec);
      // is this the first day of the month
      // Number of days since 1/mar/0000
      // 1970 * 365 is the number of days in full years
      // 1970 / 4 is the number of leap days (ignoring century rules)
      // 19 is the number of centuries
      // 4 is the number of 400 years (where there was a leap day)
      // 31 & 28 are the number of days in Jan 1970 and Feb 1970
      int day = (tv.tv_sec - the_offset) / 86400 + 1970 * 365 + 1970 / 4 - 19 + 4 - 31 - 28;

      int century = (4 * day + 3) / 146097;
      day = day - century * 146097 / 4;
      int year = (4 * day + 3) / 1461;
      day = day - year * 1461 / 4;
      int month = (5 * day + 2) / 153;
      day = day - (153 * month + 2) / 5;

      // Months 13 & 14 are really Jan and Feb in the following year.
      sntp_dbg("century=%d, year=%d, month=%d, day=%d\n", century, year, month + 3, day + 1);

      if (day == 0) {
        if (pending_LI == 1) {
          the_offset ++;
        } else {
          the_offset --;
        }
      }
      pending_LI = 0;
    }
  }
#endif
}
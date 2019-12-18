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
struct tm {int tm_mon; int tm_year; scalar_t__ tm_sec; int tm_min; int tm_hour; int const tm_mday; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */

double cs_timegm(const struct tm *tm) {
  /* Month-to-day offset for non-leap-years. */
  static const int month_day[12] = {0,   31,  59,  90,  120, 151,
                                    181, 212, 243, 273, 304, 334};

  /* Most of the calculation is easy; leap years are the main difficulty. */
  int month = tm->tm_mon % 12;
  int year = tm->tm_year + tm->tm_mon / 12;
  int year_for_leap;
  int64_t rt;

  if (month < 0) { /* Negative values % 12 are still negative. */
    month += 12;
    --year;
  }

  /* This is the number of Februaries since 1900. */
  year_for_leap = (month > 1) ? year + 1 : year;

  rt =
      tm->tm_sec /* Seconds */
      +
      60 *
          (tm->tm_min /* Minute = 60 seconds */
           +
           60 * (tm->tm_hour /* Hour = 60 minutes */
                 +
                 24 * (month_day[month] + tm->tm_mday - 1 /* Day = 24 hours */
                       + 365 * (year - 70)                /* Year = 365 days */
                       + (year_for_leap - 69) / 4 /* Every 4 years is leap... */
                       - (year_for_leap - 1) / 100 /* Except centuries... */
                       + (year_for_leap + 299) / 400))); /* Except 400s. */
  return rt < 0 ? -1 : (double) rt;
}
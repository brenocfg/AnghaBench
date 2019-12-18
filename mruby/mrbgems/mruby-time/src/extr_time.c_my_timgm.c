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
typedef  int time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */
 size_t is_leapyear (int) ; 

__attribute__((used)) static time_t
timegm(struct tm *tm)
{
  static const unsigned int ndays[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
  };
  time_t r = 0;
  int i;
  unsigned int *nday = (unsigned int*) ndays[is_leapyear(tm->tm_year+1900)];

  static const int epoch_year = 70;
  if(tm->tm_year >= epoch_year) {
    for (i = epoch_year; i < tm->tm_year; ++i)
      r += is_leapyear(i+1900) ? 366*24*60*60 : 365*24*60*60;
  } else {
    for (i = tm->tm_year; i < epoch_year; ++i)
      r -= is_leapyear(i+1900) ? 366*24*60*60 : 365*24*60*60;
  }
  for (i = 0; i < tm->tm_mon; ++i)
    r += nday[i] * 24 * 60 * 60;
  r += (tm->tm_mday - 1) * 24 * 60 * 60;
  r += tm->tm_hour * 60 * 60;
  r += tm->tm_min * 60;
  r += tm->tm_sec;
  return r;
}
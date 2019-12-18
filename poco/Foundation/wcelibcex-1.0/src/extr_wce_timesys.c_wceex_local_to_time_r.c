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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_yday; scalar_t__ tm_wday; scalar_t__ tm_isdst; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  wceex_mktime (struct tm*) ; 

time_t wceex_local_to_time_r(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm tmbuff = { 0 };

    tmbuff.tm_year = year;
    tmbuff.tm_mon = mon;
    tmbuff.tm_mday = day;
    tmbuff.tm_hour = hour;
    tmbuff.tm_min = min;
    tmbuff.tm_sec = sec;
    tmbuff.tm_isdst = 0;
    tmbuff.tm_wday = 0;
    tmbuff.tm_yday = 0;

    /* Convert tm struct to time_tUTC */
    return wceex_mktime(&tmbuff);
}
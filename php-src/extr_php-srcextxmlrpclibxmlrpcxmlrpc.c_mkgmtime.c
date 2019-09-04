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
typedef  scalar_t__ time_t ;
struct tm {int tm_year; size_t tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */

__attribute__((used)) static time_t mkgmtime(struct tm *tm)
{
    static const int mdays[12] = {0,31,59,90,120,151,181,212,243,273,304,334};

    return ((((((tm->tm_year - 70) * 365) + mdays[tm->tm_mon] + tm->tm_mday-1 +
                  (tm->tm_year-68-1+(tm->tm_mon>=2))/4) * 24) + tm->tm_hour) * 60 +
        tm->tm_min) * 60 + tm->tm_sec;
}
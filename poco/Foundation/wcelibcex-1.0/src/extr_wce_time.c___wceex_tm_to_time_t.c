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
struct tm {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_yday; } ;

/* Variables and functions */

time_t __wceex_tm_to_time_t(const struct tm *tmbuff)
{
    time_t timer;

    /* If the year is <1970 or the value is negative, the relationship is undefined */ 
    if (tmbuff->tm_year < 70)
    {
        return (time_t) -1;
    }
    
    /* If the year is >=1970 */
    /* Each and every day shall be accounted for by exactly 86400 seconds */

    timer = tmbuff->tm_sec
        + tmbuff->tm_min * 60                     /* convert minutes to seconds */
        + tmbuff->tm_hour * 3600                  /* convert hours to seconds */
        + tmbuff->tm_yday * 86400                 /* convert day of year to seconds */
        + (tmbuff->tm_year - 70) * 31536000       /* convert year to seconds */
        + ((tmbuff->tm_year - 69) / 4) * 86400        /* add a day (seconds) every 4 years starting in 1973 */
        - ((tmbuff->tm_year - 1) / 100) * 86400       /* subtract a day back out every 100 years starting in 2001 */
        + ((tmbuff->tm_year + 299) / 400) * 86400;    /* add a day back in every 400 years starting in 2001 */

    return timer;
}
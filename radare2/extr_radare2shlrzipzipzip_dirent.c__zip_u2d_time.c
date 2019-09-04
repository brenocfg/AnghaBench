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
typedef  scalar_t__ zip_uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; int tm_hour; int tm_min; int tm_sec; scalar_t__ tm_mday; } ;

/* Variables and functions */
 struct tm* localtime (int /*<<< orphan*/ *) ; 

void
_zip_u2d_time(time_t time, zip_uint16_t *dtime, zip_uint16_t *ddate)
{
    struct tm *tm;

    tm = localtime(&time);
    *ddate = (zip_uint16_t)(((tm->tm_year+1900-1980)<<9) + ((tm->tm_mon+1)<<5) + tm->tm_mday);
    *dtime = (zip_uint16_t)(((tm->tm_hour)<<11) + ((tm->tm_min)<<5) + ((tm->tm_sec)>>1));

    return;
}
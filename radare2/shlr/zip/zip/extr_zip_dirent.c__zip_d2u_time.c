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
typedef  int zip_uint16_t ;
typedef  int /*<<< orphan*/  tm ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_isdst; int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 

__attribute__((used)) static time_t
_zip_d2u_time(zip_uint16_t dtime, zip_uint16_t ddate)
{
    struct tm tm;

    memset(&tm, 0, sizeof(tm));
    
    /* let mktime decide if DST is in effect */
    tm.tm_isdst = -1;
    
    tm.tm_year = ((ddate>>9)&127) + 1980 - 1900;
    tm.tm_mon = ((ddate>>5)&15) - 1;
    tm.tm_mday = ddate&31;

    tm.tm_hour = (dtime>>11)&31;
    tm.tm_min = (dtime>>5)&63;
    tm.tm_sec = (dtime<<1)&62;

    return mktime(&tm);
}
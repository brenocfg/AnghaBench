#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_yday; int /*<<< orphan*/  tm_wday; scalar_t__ tm_isdst; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  wDayOfWeek; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; scalar_t__ wMonth; scalar_t__ wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemTime (TYPE_1__*) ; 
 scalar_t__ TM_YEAR_BASE ; 
 int /*<<< orphan*/  wceex_gmmktime (struct tm*) ; 

time_t wceex_time(time_t *timer)
{
    time_t t;
    struct tm tmbuff;
    SYSTEMTIME st;

    /* Retrive current system date time as UTC */
    GetSystemTime(&st);

    /* Build tm struct based on SYSTEMTIME values */

    /* Date values */
    tmbuff.tm_year = st.wYear - TM_YEAR_BASE;
    tmbuff.tm_mon = st.wMonth - 1;      /* wMonth value 1-12 */
    tmbuff.tm_mday = st.wDay;

    /* Time values */
    tmbuff.tm_hour = st.wHour;
    tmbuff.tm_min = st.wMinute;
    tmbuff.tm_sec = st.wSecond;
    tmbuff.tm_isdst = 0;    /* Always 0 for UTC time. */
    tmbuff.tm_wday = st.wDayOfWeek;
    tmbuff.tm_yday = 0;     /* Value is set by wceex_gmmktime */

    /* Convert tm struct to time_tUTC */
    t = wceex_gmmktime(&tmbuff);

    /* Assign time value. */
    if (timer != NULL)
    {
        *timer = t;
    }

	return t;
}
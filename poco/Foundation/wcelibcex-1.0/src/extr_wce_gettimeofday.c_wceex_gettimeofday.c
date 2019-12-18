#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timezone {int tz_minuteswest; int tz_dsttime; } ;
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int __int64 ;
struct TYPE_12__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_11__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_9__ {scalar_t__ wMonth; } ;
struct TYPE_8__ {scalar_t__ wMonth; } ;
struct TYPE_10__ {int Bias; int StandardBias; TYPE_2__ DaylightDate; TYPE_1__ StandardDate; } ;
typedef  TYPE_3__ TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  TYPE_5__ FILETIME ;

/* Variables and functions */
 scalar_t__ EPOCHFILETIME ; 
 int /*<<< orphan*/  GetSystemTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTimeZoneInformation (TYPE_3__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (int /*<<< orphan*/ *,TYPE_5__*) ; 

int wceex_gettimeofday(struct timeval *tp, struct timezone *tzp)
{
    SYSTEMTIME      st;
    FILETIME        ft;
    LARGE_INTEGER   li;
    TIME_ZONE_INFORMATION tzi;
    __int64         t;
    static int      tzflag;

    if (NULL != tp)
    {
        GetSystemTime(&st);
        SystemTimeToFileTime(&st, &ft);
        li.LowPart  = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        t  = li.QuadPart;       /* In 100-nanosecond intervals */
        t -= EPOCHFILETIME;     /* Offset to the Epoch time */
        t /= 10;                /* In microseconds */
        tp->tv_sec  = (long)(t / 1000000);
        tp->tv_usec = (long)(t % 1000000);
    }

    if (NULL != tzp)
    {   
        GetTimeZoneInformation(&tzi);

        tzp->tz_minuteswest = tzi.Bias;
        if (tzi.StandardDate.wMonth != 0)
        {
            tzp->tz_minuteswest += tzi.StandardBias * 60;
        }

        if (tzi.DaylightDate.wMonth != 0)
        {
            tzp->tz_dsttime = 1;
        }
        else
        {
            tzp->tz_dsttime = 0;
        }
    }

    return 0;
}
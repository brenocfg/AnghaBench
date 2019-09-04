#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timezone {int tz_minuteswest; int /*<<< orphan*/  tz_dsttime; } ;
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int __int64 ;
struct TYPE_5__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_4__ {int QuadPart; int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ FILETIME ;

/* Variables and functions */
 scalar_t__ EPOCHFILETIME ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_2__*) ; 
 int /*<<< orphan*/  _daylight ; 
 int _timezone ; 
 int /*<<< orphan*/  _tzset () ; 

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    FILETIME        ft;
    LARGE_INTEGER   li;
    __int64         t;
    static int      tzflag;

    if (tv)
    {
        GetSystemTimeAsFileTime(&ft);
        li.LowPart  = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        t  = li.QuadPart;       /* In 100-nanosecond intervals */
        t -= EPOCHFILETIME;     /* Offset to the Epoch time */
        t /= 10;                /* In microseconds */
        tv->tv_sec  = (long)(t / 1000000);
        tv->tv_usec = (long)(t % 1000000);
    }

    if (tz)
    {
        if (!tzflag)
        {
            _tzset();
            tzflag++;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}
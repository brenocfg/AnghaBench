#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_min; int tm_hour; int tm_year; scalar_t__ tm_mon; int /*<<< orphan*/  tm_mday; } ;
typedef  int npy_int64 ;
struct TYPE_5__ {int year; int hour; int min; scalar_t__ month; int /*<<< orphan*/  day; } ;
typedef  TYPE_1__ npy_datetimestruct ;
typedef  int NPY_TIME_T ;

/* Variables and functions */
 scalar_t__ get_datetimestruct_days (TYPE_1__*) ; 
 scalar_t__ get_localtime (int*,struct tm*) ; 
 scalar_t__ is_leapyear (int) ; 

__attribute__((used)) static int
convert_datetimestruct_utc_to_local(npy_datetimestruct *out_dts_local,
                const npy_datetimestruct *dts_utc, int *out_timezone_offset)
{
    NPY_TIME_T rawtime = 0, localrawtime;
    struct tm tm_;
    npy_int64 year_correction = 0;

    /* Make a copy of the input 'dts' to modify */
    *out_dts_local = *dts_utc;

    /*
     * For 32 bit NPY_TIME_T, the get_localtime() function does not work for
     * years later than 2038, see the comments above get_localtime(). So if the
     * year >= 2038, we instead call get_localtime() for the year 2036 or 2037
     * (depending on the leap year) which must work and at the end we add the
     * 'year_correction' back.
     */
    if (sizeof(NPY_TIME_T) == 4 && out_dts_local->year >= 2038) {
        if (is_leapyear(out_dts_local->year)) {
            /* 2036 is a leap year */
            year_correction = out_dts_local->year - 2036;
            out_dts_local->year -= year_correction; /* = 2036 */
        }
        else {
            /* 2037 is not a leap year */
            year_correction = out_dts_local->year - 2037;
            out_dts_local->year -= year_correction; /* = 2037 */
        }
    }

    /*
     * Convert everything in 'dts' to a time_t, to minutes precision.
     * This is POSIX time, which skips leap-seconds, but because
     * we drop the seconds value from the npy_datetimestruct, everything
     * is ok for this operation.
     */
    rawtime = (NPY_TIME_T)get_datetimestruct_days(out_dts_local) * 24 * 60 * 60;
    rawtime += dts_utc->hour * 60 * 60;
    rawtime += dts_utc->min * 60;

    /* localtime converts a 'time_t' into a local 'struct tm' */
    if (get_localtime(&rawtime, &tm_) < 0) {
        /* This should only fail if year < 1970 on some platforms. */
        return -1;
    }

    /* Copy back all the values except seconds */
    out_dts_local->min = tm_.tm_min;
    out_dts_local->hour = tm_.tm_hour;
    out_dts_local->day = tm_.tm_mday;
    out_dts_local->month = tm_.tm_mon + 1;
    out_dts_local->year = tm_.tm_year + 1900;

    /* Extract the timezone offset that was applied */
    rawtime /= 60;
    localrawtime = (NPY_TIME_T)get_datetimestruct_days(out_dts_local) * 24 * 60;
    localrawtime += out_dts_local->hour * 60;
    localrawtime += out_dts_local->min;

    *out_timezone_offset = localrawtime - rawtime;

    /* Reapply the year 2038 year correction */
    out_dts_local->year += year_correction;

    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
typedef  void* ngx_uint_t ;
struct TYPE_13__ {size_t ngx_tm_wday; int ngx_tm_mon; int ngx_tm_gmtoff; int /*<<< orphan*/  ngx_tm_sec; int /*<<< orphan*/  ngx_tm_min; int /*<<< orphan*/  ngx_tm_hour; int /*<<< orphan*/  ngx_tm_mday; int /*<<< orphan*/  ngx_tm_year; int /*<<< orphan*/  ngx_tm_isdst; } ;
typedef  TYPE_1__ ngx_tm_t ;
struct TYPE_14__ {scalar_t__ sec; int gmtoff; void* msec; } ;
typedef  TYPE_2__ ngx_time_t ;
typedef  void* ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int NGX_TIME_SLOTS ; 
 int /*<<< orphan*/ ** cached_err_log_time ; 
 void* cached_gmtoff ; 
 int /*<<< orphan*/ ** cached_http_log_iso8601 ; 
 int /*<<< orphan*/ ** cached_http_log_time ; 
 int /*<<< orphan*/ ** cached_http_time ; 
 int /*<<< orphan*/ ** cached_syslog_time ; 
 TYPE_2__* cached_time ; 
 int /*<<< orphan*/ * months ; 
 int /*<<< orphan*/  ngx_abs (int) ; 
 TYPE_10__ ngx_cached_err_log_time ; 
 TYPE_9__ ngx_cached_http_log_iso8601 ; 
 TYPE_8__ ngx_cached_http_log_time ; 
 TYPE_7__ ngx_cached_http_time ; 
 TYPE_6__ ngx_cached_syslog_time ; 
 TYPE_2__* ngx_cached_time ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 int /*<<< orphan*/  ngx_gettimeofday (struct timeval*) ; 
 int ngx_gettimezone () ; 
 int /*<<< orphan*/  ngx_gmtime (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_localtime (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_memory_barrier () ; 
 int /*<<< orphan*/  ngx_monotonic_time (scalar_t__,void*) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ngx_time_lock ; 
 void* ngx_timezone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_unlock (int /*<<< orphan*/ *) ; 
 size_t slot ; 
 int /*<<< orphan*/ * week ; 

void
ngx_time_update(void)
{
    u_char          *p0, *p1, *p2, *p3, *p4;
    ngx_tm_t         tm, gmt;
    time_t           sec;
    ngx_uint_t       msec;
    ngx_time_t      *tp;
    struct timeval   tv;

    if (!ngx_trylock(&ngx_time_lock)) {
        return;
    }

    ngx_gettimeofday(&tv);

    sec = tv.tv_sec;
    msec = tv.tv_usec / 1000;

    ngx_current_msec = ngx_monotonic_time(sec, msec);

    tp = &cached_time[slot];

    if (tp->sec == sec) {
        tp->msec = msec;
        ngx_unlock(&ngx_time_lock);
        return;
    }

    if (slot == NGX_TIME_SLOTS - 1) {
        slot = 0;
    } else {
        slot++;
    }

    tp = &cached_time[slot];

    tp->sec = sec;
    tp->msec = msec;

    ngx_gmtime(sec, &gmt);


    p0 = &cached_http_time[slot][0];

    (void) ngx_sprintf(p0, "%s, %02d %s %4d %02d:%02d:%02d GMT",
                       week[gmt.ngx_tm_wday], gmt.ngx_tm_mday,
                       months[gmt.ngx_tm_mon - 1], gmt.ngx_tm_year,
                       gmt.ngx_tm_hour, gmt.ngx_tm_min, gmt.ngx_tm_sec);

#if (NGX_HAVE_GETTIMEZONE)

    tp->gmtoff = ngx_gettimezone();
    ngx_gmtime(sec + tp->gmtoff * 60, &tm);

#elif (NGX_HAVE_GMTOFF)

    ngx_localtime(sec, &tm);
    cached_gmtoff = (ngx_int_t) (tm.ngx_tm_gmtoff / 60);
    tp->gmtoff = cached_gmtoff;

#else

    ngx_localtime(sec, &tm);
    cached_gmtoff = ngx_timezone(tm.ngx_tm_isdst);
    tp->gmtoff = cached_gmtoff;

#endif


    p1 = &cached_err_log_time[slot][0];

    (void) ngx_sprintf(p1, "%4d/%02d/%02d %02d:%02d:%02d",
                       tm.ngx_tm_year, tm.ngx_tm_mon,
                       tm.ngx_tm_mday, tm.ngx_tm_hour,
                       tm.ngx_tm_min, tm.ngx_tm_sec);


    p2 = &cached_http_log_time[slot][0];

    (void) ngx_sprintf(p2, "%02d/%s/%d:%02d:%02d:%02d %c%02i%02i",
                       tm.ngx_tm_mday, months[tm.ngx_tm_mon - 1],
                       tm.ngx_tm_year, tm.ngx_tm_hour,
                       tm.ngx_tm_min, tm.ngx_tm_sec,
                       tp->gmtoff < 0 ? '-' : '+',
                       ngx_abs(tp->gmtoff / 60), ngx_abs(tp->gmtoff % 60));

    p3 = &cached_http_log_iso8601[slot][0];

    (void) ngx_sprintf(p3, "%4d-%02d-%02dT%02d:%02d:%02d%c%02i:%02i",
                       tm.ngx_tm_year, tm.ngx_tm_mon,
                       tm.ngx_tm_mday, tm.ngx_tm_hour,
                       tm.ngx_tm_min, tm.ngx_tm_sec,
                       tp->gmtoff < 0 ? '-' : '+',
                       ngx_abs(tp->gmtoff / 60), ngx_abs(tp->gmtoff % 60));

    p4 = &cached_syslog_time[slot][0];

    (void) ngx_sprintf(p4, "%s %2d %02d:%02d:%02d",
                       months[tm.ngx_tm_mon - 1], tm.ngx_tm_mday,
                       tm.ngx_tm_hour, tm.ngx_tm_min, tm.ngx_tm_sec);

    ngx_memory_barrier();

    ngx_cached_time = tp;
    ngx_cached_http_time.data = p0;
    ngx_cached_err_log_time.data = p1;
    ngx_cached_http_log_time.data = p2;
    ngx_cached_http_log_iso8601.data = p3;
    ngx_cached_syslog_time.data = p4;

    ngx_unlock(&ngx_time_lock);
}
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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_3__ {int epoch; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_op_t ;
typedef  int int64_t ;

/* Variables and functions */
 int ngx_current_msec ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,scalar_t__) ; 

__attribute__((used)) static u_char *
ngx_rtmp_log_var_session_readable_time_getdata(ngx_rtmp_session_t *s,
    u_char *buf, ngx_rtmp_log_op_t *op)
{
    int64_t     v;
    ngx_uint_t  days, hours, minutes, seconds;

    v = (ngx_current_msec - s->epoch) / 1000;

    days = (ngx_uint_t) (v / (60 * 60 * 24));
    hours = (ngx_uint_t) (v / (60 * 60) % 24);
    minutes = (ngx_uint_t) (v / 60 % 60);
    seconds = (ngx_uint_t) (v % 60);

    if (days) {
        buf = ngx_sprintf(buf, "%uid ", days);
    }

    if (days || hours) {
        buf = ngx_sprintf(buf, "%uih ", hours);
    }

    if (days || hours || minutes) {
        buf = ngx_sprintf(buf, "%uim ", minutes);
    }

    buf = ngx_sprintf(buf, "%uis", seconds);

    return buf;
}
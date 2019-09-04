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
struct TYPE_3__ {int /*<<< orphan*/  msec; int /*<<< orphan*/  sec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_op_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_timeofday () ; 

__attribute__((used)) static u_char *
ngx_rtmp_log_var_msec_getdata(ngx_rtmp_session_t *s, u_char *buf,
    ngx_rtmp_log_op_t *op)
{
    ngx_time_t  *tp;

    tp = ngx_timeofday();
    
    return ngx_sprintf(buf, "%T.%03M", tp->sec, tp->msec);
}
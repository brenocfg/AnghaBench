#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_10__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_11__ {int /*<<< orphan*/  conf; } ;
typedef  TYPE_3__ ngx_rtmp_exec_t ;
struct TYPE_12__ {scalar_t__ nelts; TYPE_3__* elts; } ;
typedef  TYPE_4__ ngx_array_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,scalar_t__) ; 
 scalar_t__ ngx_rtmp_exec_filter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_run (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_rtmp_exec_managed(ngx_rtmp_session_t *s, ngx_array_t *e, const char *op)
{
    ngx_uint_t        n;
    ngx_rtmp_exec_t  *en;

    if (e->nelts == 0) {
        return;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "exec: %s %uz managed command(s)", op, e->nelts);

    en = e->elts;
    for (n = 0; n < e->nelts; n++, en++) {
        if (ngx_rtmp_exec_filter(s, en->conf) == NGX_OK) {
            ngx_rtmp_exec_run(en);
        }
    }
}
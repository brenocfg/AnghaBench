#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int ping_active; TYPE_1__* connection; scalar_t__ ping_reset; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_15__ {int /*<<< orphan*/  ping_timeout; scalar_t__ busy; } ;
typedef  TYPE_3__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_16__ {TYPE_5__* data; } ;
typedef  TYPE_4__ ngx_event_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; TYPE_2__* data; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_current_msec ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 
 TYPE_3__* ngx_rtmp_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_reset_ping (TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_send_ping_request (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_ping(ngx_event_t *pev)
{
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;
    ngx_rtmp_core_srv_conf_t   *cscf;

    c = pev->data;
    s = c->data;

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    /* i/o event has happened; no need to ping */
    if (s->ping_reset) {
        ngx_rtmp_reset_ping(s);
        return;
    }

    if (s->ping_active) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
                "ping: unresponded");
        ngx_rtmp_finalize_session(s);
        return;
    }

    if (cscf->busy) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
                "ping: not busy between pings");
        ngx_rtmp_finalize_session(s);
        return;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "ping: schedule %Mms", cscf->ping_timeout);

    if (ngx_rtmp_send_ping_request(s, (uint32_t)ngx_current_msec) != NGX_OK) {
        ngx_rtmp_finalize_session(s);
        return;
    }

    s->ping_active = 1;
    ngx_add_timer(pev, cscf->ping_timeout);
}
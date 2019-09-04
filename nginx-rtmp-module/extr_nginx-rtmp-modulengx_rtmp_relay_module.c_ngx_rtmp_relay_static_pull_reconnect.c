#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_8__* target; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_2__ ngx_rtmp_relay_static_t ;
struct TYPE_13__ {TYPE_5__* static_evt; TYPE_1__* session; } ;
typedef  TYPE_3__ ngx_rtmp_relay_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/  pull_reconnect; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_rtmp_relay_app_conf_t ;
struct TYPE_15__ {TYPE_2__* data; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int static_relay; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_relay_create_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 

__attribute__((used)) static void
ngx_rtmp_relay_static_pull_reconnect(ngx_event_t *ev)
{
    ngx_rtmp_relay_static_t    *rs = ev->data;

    ngx_rtmp_relay_ctx_t       *ctx;
    ngx_rtmp_relay_app_conf_t  *racf;

    racf = ngx_rtmp_get_module_app_conf(&rs->cctx, ngx_rtmp_relay_module);

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, racf->log, 0,
                   "relay: reconnecting static pull");

    ctx = ngx_rtmp_relay_create_connection(&rs->cctx, &rs->target->name,
                                           rs->target);
    if (ctx) {
        ctx->session->static_relay = 1;
        ctx->static_evt = ev;
        return;
    }

    ngx_add_timer(ev, racf->pull_reconnect);
}
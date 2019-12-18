#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_rtmp_session_t ;
struct TYPE_23__ {scalar_t__ timer_set; int /*<<< orphan*/  handler; int /*<<< orphan*/  log; TYPE_1__* data; } ;
struct TYPE_21__ {unsigned int active; scalar_t__ publishing; TYPE_3__* cs; int /*<<< orphan*/  silent; TYPE_4__* session; struct TYPE_21__* next; TYPE_2__* stream; TYPE_7__ idle_evt; } ;
typedef  TYPE_5__ ngx_rtmp_live_ctx_t ;
struct TYPE_22__ {scalar_t__ idle_timeout; } ;
typedef  TYPE_6__ ngx_rtmp_live_app_conf_t ;
typedef  TYPE_7__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_19__ {scalar_t__ dropped; scalar_t__ active; } ;
struct TYPE_18__ {unsigned int active; TYPE_5__* ctx; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_4__*) ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_live_idle ; 
 int /*<<< orphan*/  ngx_rtmp_live_module ; 
 scalar_t__ ngx_rtmp_send_message (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_live_set_status(ngx_rtmp_session_t *s, ngx_chain_t *control,
                         ngx_chain_t **status, size_t nstatus,
                         unsigned active)
{
    ngx_rtmp_live_app_conf_t   *lacf;
    ngx_rtmp_live_ctx_t        *ctx, *pctx;
    ngx_chain_t               **cl;
    ngx_event_t                *e;
    size_t                      n;

    lacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_live_module);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_live_module);

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "live: set active=%ui", active);

    if (ctx->active == active) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "live: unchanged active=%ui", active);
        return;
    }

    ctx->active = active;

    if (ctx->publishing) {

        /* publisher */

        if (lacf->idle_timeout) {
            e = &ctx->idle_evt;

            if (active && !ctx->idle_evt.timer_set) {
                e->data = s->connection;
                e->log = s->connection->log;
                e->handler = ngx_rtmp_live_idle;

                ngx_add_timer(e, lacf->idle_timeout);

            } else if (!active && ctx->idle_evt.timer_set) {
                ngx_del_timer(e);
            }
        }

        ctx->stream->active = active;

        for (pctx = ctx->stream->ctx; pctx; pctx = pctx->next) {
            if (pctx->publishing == 0) {
                ngx_rtmp_live_set_status(pctx->session, control, status,
                                         nstatus, active);
            }
        }

        return;
    }

    /* subscriber */

    if (control && ngx_rtmp_send_message(s, control, 0) != NGX_OK) {
        ngx_rtmp_finalize_session(s);
        return;
    }

    if (!ctx->silent) {
        cl = status;

        for (n = 0; n < nstatus; ++n, ++cl) {
            if (*cl && ngx_rtmp_send_message(s, *cl, 0) != NGX_OK) {
                ngx_rtmp_finalize_session(s);
                return;
            }
        }
    }

    ctx->cs[0].active = 0;
    ctx->cs[0].dropped = 0;

    ctx->cs[1].active = 0;
    ctx->cs[1].dropped = 0;
}
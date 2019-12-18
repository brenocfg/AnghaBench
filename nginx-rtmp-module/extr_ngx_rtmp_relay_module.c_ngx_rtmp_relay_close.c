#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_19__ {scalar_t__ relay; scalar_t__ static_relay; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {scalar_t__ timer_set; } ;
struct TYPE_20__ {struct TYPE_20__* next; TYPE_11__ name; struct TYPE_20__* publish; TYPE_10__* session; int /*<<< orphan*/  app; struct TYPE_20__* play; TYPE_13__ push_evt; int /*<<< orphan*/ * tag; TYPE_13__* static_evt; } ;
typedef  TYPE_3__ ngx_rtmp_relay_ctx_t ;
struct TYPE_21__ {size_t nbuckets; TYPE_3__** ctx; int /*<<< orphan*/  push_reconnect; int /*<<< orphan*/  pull_reconnect; } ;
typedef  TYPE_4__ ngx_rtmp_relay_app_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {TYPE_1__* connection; scalar_t__ relay; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_13__*) ; 
 size_t ngx_hash_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_11__*,size_t) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_10__*) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 

__attribute__((used)) static void
ngx_rtmp_relay_close(ngx_rtmp_session_t *s)
{
    ngx_rtmp_relay_app_conf_t          *racf;
    ngx_rtmp_relay_ctx_t               *ctx, **cctx;
    ngx_uint_t                          hash;

    racf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_relay_module);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_relay_module);
    if (ctx == NULL) {
        return;
    }

    if (s->static_relay) {
        ngx_add_timer(ctx->static_evt, racf->pull_reconnect);
    }

    if (ctx->publish == NULL) {
        return;
    }

    /* play end disconnect? */
    if (ctx->publish != ctx) {
        for (cctx = &ctx->publish->play; *cctx; cctx = &(*cctx)->next) {
            if (*cctx == ctx) {
                *cctx = ctx->next;
                break;
            }
        }

        ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ctx->session->connection->log, 0,
                "relay: play disconnect app='%V' name='%V'",
                &ctx->app, &ctx->name);

        /* push reconnect */
        if (s->relay && ctx->tag == &ngx_rtmp_relay_module &&
            !ctx->publish->push_evt.timer_set)
        {
            ngx_add_timer(&ctx->publish->push_evt, racf->push_reconnect);
        }

#ifdef NGX_DEBUG
        {
            ngx_uint_t  n = 0;
            for (cctx = &ctx->publish->play; *cctx; cctx = &(*cctx)->next, ++n);
            ngx_log_debug3(NGX_LOG_DEBUG_RTMP, ctx->session->connection->log, 0,
                "relay: play left after disconnect app='%V' name='%V': %ui",
                &ctx->app, &ctx->name, n);
        }
#endif

        if (ctx->publish->play == NULL && ctx->publish->session->relay) {
            ngx_log_debug2(NGX_LOG_DEBUG_RTMP,
                 ctx->publish->session->connection->log, 0,
                "relay: publish disconnect empty app='%V' name='%V'",
                &ctx->app, &ctx->name);
            ngx_rtmp_finalize_session(ctx->publish->session);
        }

        ctx->publish = NULL;

        return;
    }

    /* publish end disconnect */
    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, ctx->session->connection->log, 0,
            "relay: publish disconnect app='%V' name='%V'",
            &ctx->app, &ctx->name);

    if (ctx->push_evt.timer_set) {
        ngx_del_timer(&ctx->push_evt);
    }

    for (cctx = &ctx->play; *cctx; cctx = &(*cctx)->next) {
        (*cctx)->publish = NULL;
        ngx_log_debug2(NGX_LOG_DEBUG_RTMP, (*cctx)->session->connection->log,
            0, "relay: play disconnect orphan app='%V' name='%V'",
            &(*cctx)->app, &(*cctx)->name);
        ngx_rtmp_finalize_session((*cctx)->session);
    }
    ctx->publish = NULL;

    hash = ngx_hash_key(ctx->name.data, ctx->name.len);
    cctx = &racf->ctx[hash % racf->nbuckets];
    for (; *cctx && *cctx != ctx; cctx = &(*cctx)->next);
    if (*cctx) {
        *cctx = ctx->next;
    }
}
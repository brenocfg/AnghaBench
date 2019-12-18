#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_12__ {int joined; struct TYPE_12__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_play_ctx_t ;
struct TYPE_13__ {size_t nbuckets; TYPE_3__** ctx; } ;
typedef  TYPE_4__ ngx_rtmp_play_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_NAME ; 
 size_t ngx_hash_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_join(ngx_rtmp_session_t *s)
{
    ngx_rtmp_play_ctx_t        *ctx, **pctx;
    ngx_rtmp_play_app_conf_t   *pacf;
    ngx_uint_t                  h;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: join");

    pacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_play_module);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);
    if (ctx == NULL || ctx->joined) {
        return NGX_ERROR;
    }

    h = ngx_hash_key(ctx->name, ngx_strlen(ctx->name));
    pctx = &pacf->ctx[h % pacf->nbuckets];

    while (*pctx) {
        if (!ngx_strncmp((*pctx)->name, ctx->name, NGX_RTMP_MAX_NAME)) {
            break;
        }
        pctx = &(*pctx)->next;
    }

    ctx->next = *pctx;
    *pctx = ctx;
    ctx->joined = 1;

    return NGX_OK;
}
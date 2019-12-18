#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_14__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_relay_target_t ;
struct TYPE_12__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  log; TYPE_3__* data; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; scalar_t__ publish; TYPE_1__ push_evt; TYPE_3__* session; } ;
typedef  TYPE_4__ ngx_rtmp_relay_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_relay_copy_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 
 int /*<<< orphan*/  ngx_rtmp_relay_push_reconnect ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_rtmp_relay_ctx_t *
ngx_rtmp_relay_create_local_ctx(ngx_rtmp_session_t *s, ngx_str_t *name,
        ngx_rtmp_relay_target_t *target)
{
    ngx_rtmp_relay_ctx_t           *ctx;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "relay: create local context");

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_relay_module);
    if (ctx == NULL) {
        ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_relay_ctx_t));
        if (ctx == NULL) {
            return NULL;
        }
        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_relay_module);
    }
    ctx->session = s;

    ctx->push_evt.data = s;
    ctx->push_evt.log = s->connection->log;
    ctx->push_evt.handler = ngx_rtmp_relay_push_reconnect;

    if (ctx->publish) {
        return NULL;
    }

    if (ngx_rtmp_relay_copy_str(s->connection->pool, &ctx->name, name)
            != NGX_OK)
    {
        return NULL;
    }

    return ctx;
}
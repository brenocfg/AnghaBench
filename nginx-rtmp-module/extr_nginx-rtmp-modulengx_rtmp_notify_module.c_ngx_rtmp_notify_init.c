#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_18__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_21__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  log; TYPE_1__* data; scalar_t__ timer_set; } ;
struct TYPE_19__ {TYPE_5__ update_evt; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_notify_ctx_t ;
struct TYPE_20__ {scalar_t__ update_timeout; int /*<<< orphan*/ ** url; int /*<<< orphan*/  active; } ;
typedef  TYPE_4__ ngx_rtmp_notify_app_conf_t ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
struct TYPE_16__ {int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_ARGS ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_NAME ; 
 size_t NGX_RTMP_NOTIFY_UPDATE ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,scalar_t__) ; 
 TYPE_14__* ngx_cached_time ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 int /*<<< orphan*/  ngx_rtmp_notify_update ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_rtmp_notify_init(ngx_rtmp_session_t *s,
        u_char name[NGX_RTMP_MAX_NAME], u_char args[NGX_RTMP_MAX_ARGS],
        ngx_uint_t flags)
{
    ngx_rtmp_notify_ctx_t          *ctx;
    ngx_rtmp_notify_app_conf_t     *nacf;
    ngx_event_t                    *e;

    nacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_notify_module);
    if (!nacf->active) {
        return;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_notify_module);

    if (ctx == NULL) {
        ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_notify_ctx_t));
        if (ctx == NULL) {
            return;
        }

        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_notify_module);
    }

    ngx_memcpy(ctx->name, name, NGX_RTMP_MAX_NAME);
    ngx_memcpy(ctx->args, args, NGX_RTMP_MAX_ARGS);

    ctx->flags |= flags;

    if (nacf->url[NGX_RTMP_NOTIFY_UPDATE] == NULL ||
        nacf->update_timeout == 0)
    {
        return;
    }

    if (ctx->update_evt.timer_set) {
        return;
    }

    ctx->start = ngx_cached_time->sec;

    e = &ctx->update_evt;

    e->data = s->connection;
    e->log = s->connection->log;
    e->handler = ngx_rtmp_notify_update;

    ngx_add_timer(e, nacf->update_timeout);

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "notify: schedule initial update %Mms",
                   nacf->update_timeout);
}
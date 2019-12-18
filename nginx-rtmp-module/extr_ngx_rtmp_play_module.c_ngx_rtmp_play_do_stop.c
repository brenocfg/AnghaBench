#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_15__ {scalar_t__ prev; scalar_t__ posted; scalar_t__ timer_set; } ;
struct TYPE_14__ {scalar_t__ playing; int /*<<< orphan*/  file; TYPE_2__* fmt; TYPE_9__ send_evt; } ;
typedef  TYPE_4__ ngx_rtmp_play_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {scalar_t__ (* stop ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_delete_posted_event (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_do_stop(ngx_rtmp_session_t *s)
{
    ngx_rtmp_play_ctx_t            *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: stop");

    if (ctx->send_evt.timer_set) {
        ngx_del_timer(&ctx->send_evt);
    }

#if (nginx_version >= 1007005)
    if (ctx->send_evt.posted)
#else
    if (ctx->send_evt.prev)
#endif
    {
        ngx_delete_posted_event((&ctx->send_evt));
    }

    if (ctx->fmt && ctx->fmt->stop &&
        ctx->fmt->stop(s, &ctx->file) != NGX_OK)
    {
        return NGX_ERROR;
    }

    ctx->playing = 0;

    return NGX_OK;
}
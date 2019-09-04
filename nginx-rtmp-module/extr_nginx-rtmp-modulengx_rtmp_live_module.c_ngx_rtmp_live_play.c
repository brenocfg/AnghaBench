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

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_18__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_19__ {int /*<<< orphan*/  silent; int /*<<< orphan*/  name; scalar_t__ reset; scalar_t__ duration; scalar_t__ start; } ;
typedef  TYPE_3__ ngx_rtmp_play_t ;
struct TYPE_20__ {int /*<<< orphan*/  silent; } ;
typedef  TYPE_4__ ngx_rtmp_live_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/  play_restart; int /*<<< orphan*/  live; } ;
typedef  TYPE_5__ ngx_rtmp_live_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  next_play (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_live_join (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_live_module ; 
 int /*<<< orphan*/  ngx_rtmp_send_sample_access (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_send_status (TYPE_2__*,char*,char*,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_live_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    ngx_rtmp_live_app_conf_t       *lacf;
    ngx_rtmp_live_ctx_t            *ctx;

    lacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_live_module);

    if (lacf == NULL || !lacf->live) {
        goto next;
    }

    ngx_log_debug4(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "live: play: name='%s' start=%uD duration=%uD reset=%d",
                   v->name, (uint32_t) v->start,
                   (uint32_t) v->duration, (uint32_t) v->reset);

    /* join stream as subscriber */

    ngx_rtmp_live_join(s, v->name, 0);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_live_module);
    if (ctx == NULL) {
        goto next;
    }

    ctx->silent = v->silent;

    if (!ctx->silent && !lacf->play_restart) {
        ngx_rtmp_send_status(s, "NetStream.Play.Start",
                             "status", "Start live");
        ngx_rtmp_send_sample_access(s);
    }

next:
    return next_play(s, v);
}
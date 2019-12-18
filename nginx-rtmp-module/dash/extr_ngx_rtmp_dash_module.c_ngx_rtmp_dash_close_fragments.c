#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_12__ {scalar_t__ opened; int /*<<< orphan*/  id; int /*<<< orphan*/  audio; int /*<<< orphan*/  video; } ;
typedef  TYPE_3__ ngx_rtmp_dash_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_dash_close_fragment (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_dash_module ; 
 int /*<<< orphan*/  ngx_rtmp_dash_next_frag (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_dash_write_playlist (TYPE_2__*) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_dash_close_fragments(ngx_rtmp_session_t *s)
{
    ngx_rtmp_dash_ctx_t  *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_dash_module);
    if (ctx == NULL || !ctx->opened) {
        return NGX_OK;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "dash: close fragments");

    ngx_rtmp_dash_close_fragment(s, &ctx->video);
    ngx_rtmp_dash_close_fragment(s, &ctx->audio);

    ngx_rtmp_dash_next_frag(s);

    ngx_rtmp_dash_write_playlist(s);

    ctx->id++;
    ctx->opened = 0;

    return NGX_OK;
}
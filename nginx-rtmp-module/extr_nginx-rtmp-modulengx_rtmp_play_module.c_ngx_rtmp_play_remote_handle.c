#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_16__ {int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_play_t ;
struct TYPE_17__ {scalar_t__ nbody; scalar_t__ file_id; } ;
typedef  TYPE_4__ ngx_rtmp_play_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  next_play (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_copy_local_file (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 int /*<<< orphan*/  ngx_rtmp_play_next_entry (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ ngx_rtmp_play_open (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_remote_handle(ngx_rtmp_session_t *s, void *arg, ngx_chain_t *in)
{
    ngx_rtmp_play_t        *v = arg;

    ngx_rtmp_play_ctx_t    *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);

    if (ctx->nbody == 0) {
        return ngx_rtmp_play_next_entry(s, v);
    }

    if (ctx->file_id) {
        ngx_rtmp_play_copy_local_file(s, v->name);
    }

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: open remote file");

    if (ngx_rtmp_play_open(s, v->start) != NGX_OK) {
        return NGX_ERROR;
    }

    return next_play(s, (ngx_rtmp_play_t *)arg);
}
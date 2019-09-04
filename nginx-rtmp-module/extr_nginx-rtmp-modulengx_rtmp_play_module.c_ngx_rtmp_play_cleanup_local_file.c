#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_10__ {scalar_t__ file_id; } ;
typedef  TYPE_3__ ngx_rtmp_play_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  ngx_delete_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_play_get_local_file_path (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 

__attribute__((used)) static void
ngx_rtmp_play_cleanup_local_file(ngx_rtmp_session_t *s)
{
    ngx_rtmp_play_ctx_t        *ctx;
    u_char                     *path;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);
    if (ctx == NULL || ctx->file_id == 0) {
        return;
    }

    path = ngx_rtmp_play_get_local_file_path(s);

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "play: deleting local file '%s'", path);

    ctx->file_id = 0;

    ngx_delete_file(path);
}
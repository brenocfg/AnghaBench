#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_9__ {int offset; scalar_t__ msg_mask; int /*<<< orphan*/  epoch; int /*<<< orphan*/  start_timestamp; } ;
typedef  TYPE_3__ ngx_rtmp_flv_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_file_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_current_msec ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_flv_module ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_flv_seek(ngx_rtmp_session_t *s, ngx_file_t *f, ngx_uint_t timestamp)
{
    ngx_rtmp_flv_ctx_t             *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_flv_module);

    if (ctx == NULL) {
        return NGX_OK;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                  "flv: seek timestamp=%ui", timestamp);

    ctx->start_timestamp = timestamp;
    ctx->epoch = ngx_current_msec;
    ctx->offset = -1;
    ctx->msg_mask = 0;

    return NGX_OK;
}
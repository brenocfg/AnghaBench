#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_record_rec_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_record_get_node_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_record_make_path (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_rtmp_record_node_close (TYPE_2__*,int /*<<< orphan*/ *) ; 

ngx_int_t
ngx_rtmp_record_close(ngx_rtmp_session_t *s, ngx_uint_t n, ngx_str_t *path)
{
    ngx_rtmp_record_rec_ctx_t      *rctx;
    ngx_int_t                       rc;

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "record: #%ui manual close", n);

    rctx = ngx_rtmp_record_get_node_ctx(s, n);

    if (rctx == NULL) {
        return NGX_ERROR;
    }

    rc = ngx_rtmp_record_node_close(s, rctx);
    if (rc != NGX_OK) {
        return rc;
    }

    if (path) {
        ngx_rtmp_record_make_path(s, rctx, path);
    }

    return NGX_OK;
}
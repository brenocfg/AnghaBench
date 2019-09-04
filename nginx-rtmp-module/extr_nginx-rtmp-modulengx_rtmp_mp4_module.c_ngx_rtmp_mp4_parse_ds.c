#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_10__ {size_t header_size; int /*<<< orphan*/ * header; } ;
typedef  TYPE_3__ ngx_rtmp_mp4_track_t ;
struct TYPE_11__ {TYPE_3__* track; } ;
typedef  TYPE_4__ ngx_rtmp_mp4_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_parse_ds(ngx_rtmp_session_t *s, u_char *pos, u_char *last)
{
    ngx_rtmp_mp4_ctx_t     *ctx;
    ngx_rtmp_mp4_track_t   *t;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_mp4_module);

    t = ctx->track;

    if (t == NULL) {
        return NGX_OK;
    }

    t->header = pos;
    t->header_size = (size_t) (last - pos);

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "mp4: decoder header size=%uz", t->header_size);

    return NGX_OK;
}
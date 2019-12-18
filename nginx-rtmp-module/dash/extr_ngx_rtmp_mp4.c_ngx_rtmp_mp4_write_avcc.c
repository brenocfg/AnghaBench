#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_11__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_12__ {TYPE_5__* avc_header; } ;
typedef  TYPE_4__ ngx_rtmp_codec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_13__ {TYPE_1__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;
struct TYPE_9__ {int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_codec_module ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_rtmp_mp4_start_box (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_mp4_update_box_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_mp4_write_avcc(ngx_rtmp_session_t *s, ngx_buf_t *b)
{
    u_char                *pos, *p;
    ngx_chain_t           *in;
    ngx_rtmp_codec_ctx_t  *codec_ctx;

    codec_ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_codec_module);

    if (codec_ctx == NULL) {
        return NGX_ERROR;
    }

    in = codec_ctx->avc_header;
    if (in == NULL) {
        return NGX_ERROR;
    }

    pos = ngx_rtmp_mp4_start_box(b, "avcC");

    /* assume config fits one chunk (highly probable) */

    /*
     * Skip:
     * - flv fmt
     * - H264 CONF/PICT (0x00)
     * - 0
     * - 0
     * - 0
     */

    p = in->buf->pos + 5;

    if (p < in->buf->last) {
        ngx_rtmp_mp4_data(b, p, (size_t) (in->buf->last - p));
    } else {
        ngx_log_error(NGX_LOG_ERR, s->connection->log, ngx_errno,
                      "dash: invalid avcc received");
    }

    ngx_rtmp_mp4_update_box_size(b, pos);

    return NGX_OK;
}
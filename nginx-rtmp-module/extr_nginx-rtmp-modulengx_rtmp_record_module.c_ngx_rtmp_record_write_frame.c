#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  void* u_char ;
struct TYPE_19__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_24__ {scalar_t__ offset; int /*<<< orphan*/  fd; } ;
struct TYPE_20__ {int video; int audio; int epoch; scalar_t__ nframes; TYPE_8__ file; TYPE_5__* conf; } ;
typedef  TYPE_4__ ngx_rtmp_record_rec_ctx_t ;
struct TYPE_21__ {scalar_t__ max_frames; scalar_t__ max_size; int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ ngx_rtmp_record_app_conf_t ;
struct TYPE_22__ {int mlen; scalar_t__ type; int timestamp; } ;
typedef  TYPE_6__ ngx_rtmp_header_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_23__ {TYPE_2__* buf; struct TYPE_23__* next; } ;
typedef  TYPE_7__ ngx_chain_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_18__ {void** pos; void** last; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_RTMP_MSG_VIDEO ; 
 int /*<<< orphan*/  ngx_close_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_rtmp_record_node_close (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_rtmp_record_notify_error (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ngx_write_file (TYPE_8__*,void**,int,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_write_frame(ngx_rtmp_session_t *s,
                            ngx_rtmp_record_rec_ctx_t *rctx,
                            ngx_rtmp_header_t *h, ngx_chain_t *in,
                            ngx_int_t inc_nframes)
{
    u_char                      hdr[11], *p, *ph;
    uint32_t                    timestamp, tag_size;
    ngx_rtmp_record_app_conf_t *rracf;

    rracf = rctx->conf;

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "record: %V frame: mlen=%uD",
                   &rracf->id, h->mlen);

    if (h->type == NGX_RTMP_MSG_VIDEO) {
        rctx->video = 1;
    } else {
        rctx->audio = 1;
    }

    timestamp = h->timestamp - rctx->epoch;

    if ((int32_t) timestamp < 0) {
        ngx_log_debug2(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                       "record: %V cut timestamp=%D", &rracf->id, timestamp);

        timestamp = 0;
    }

    /* write tag header */
    ph = hdr;

    *ph++ = (u_char)h->type;

    p = (u_char*)&h->mlen;
    *ph++ = p[2];
    *ph++ = p[1];
    *ph++ = p[0];

    p = (u_char*)&timestamp;
    *ph++ = p[2];
    *ph++ = p[1];
    *ph++ = p[0];
    *ph++ = p[3];

    *ph++ = 0;
    *ph++ = 0;
    *ph++ = 0;

    tag_size = (ph - hdr) + h->mlen;

    if (ngx_write_file(&rctx->file, hdr, ph - hdr, rctx->file.offset)
        == NGX_ERROR)
    {
        ngx_rtmp_record_notify_error(s, rctx);

        ngx_close_file(rctx->file.fd);

        return NGX_ERROR;
    }

    /* write tag body
     * FIXME: NGINX
     * ngx_write_chain seems to fit best
     * but it suffers from uncontrollable
     * allocations.
     * we're left with plain writing */
    for(; in; in = in->next) {
        if (in->buf->pos == in->buf->last) {
            continue;
        }

        if (ngx_write_file(&rctx->file, in->buf->pos, in->buf->last
                           - in->buf->pos, rctx->file.offset)
            == NGX_ERROR)
        {
            return NGX_ERROR;
        }
    }

    /* write tag size */
    ph = hdr;
    p = (u_char*)&tag_size;

    *ph++ = p[3];
    *ph++ = p[2];
    *ph++ = p[1];
    *ph++ = p[0];

    if (ngx_write_file(&rctx->file, hdr, ph - hdr,
                       rctx->file.offset)
        == NGX_ERROR)
    {
        return NGX_ERROR;
    }

    rctx->nframes += inc_nframes;

    /* watch max size */
    if ((rracf->max_size && rctx->file.offset >= (ngx_int_t) rracf->max_size) ||
        (rracf->max_frames && rctx->nframes >= rracf->max_frames))
    {
        ngx_rtmp_record_node_close(s, rctx);
    }

    return NGX_OK;
}
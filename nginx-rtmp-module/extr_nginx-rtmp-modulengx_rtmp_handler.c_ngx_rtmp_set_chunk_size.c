#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_13__ {int in_chunk_size_changing; TYPE_2__* in_streams; scalar_t__ in_old_pool; TYPE_1__* connection; scalar_t__ in_pool; scalar_t__ in_chunk_size; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_14__ {size_t max_streams; } ;
typedef  TYPE_4__ ngx_rtmp_core_srv_conf_t ;
typedef  size_t ngx_int_t ;
struct TYPE_15__ {struct TYPE_15__* next; TYPE_6__* buf; } ;
typedef  TYPE_5__ ngx_chain_t ;
struct TYPE_16__ {scalar_t__ end; scalar_t__ last; scalar_t__ pos; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_12__ {TYPE_5__* in; } ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 size_t NGX_OK ; 
 scalar_t__ NGX_RTMP_MAX_CHUNK_SIZE ; 
 scalar_t__ ngx_cpymem (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 void* ngx_rtmp_alloc_in_buf (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_4__* ngx_rtmp_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_rtmp_set_chunk_size(ngx_rtmp_session_t *s, ngx_uint_t size)
{
    ngx_rtmp_core_srv_conf_t           *cscf;
    ngx_chain_t                        *li, *fli, *lo, *flo;
    ngx_buf_t                          *bi, *bo;
    ngx_int_t                           n;

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
        "setting chunk_size=%ui", size);

    if (size > NGX_RTMP_MAX_CHUNK_SIZE) {
        ngx_log_error(NGX_LOG_ALERT, s->connection->log, 0,
                      "too big RTMP chunk size:%ui", size);
        return NGX_ERROR;
    }

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    s->in_old_pool = s->in_pool;
    s->in_chunk_size = size;
    s->in_pool = ngx_create_pool(4096, s->connection->log);

    /* copy existing chunk data */
    if (s->in_old_pool) {
        s->in_chunk_size_changing = 1;
        s->in_streams[0].in = NULL;

        for(n = 1; n < cscf->max_streams; ++n) {
            /* stream buffer is circular
             * for all streams except for the current one
             * (which caused this chunk size change);
             * we can simply ignore it */
            li = s->in_streams[n].in;
            if (li == NULL || li->next == NULL) {
                s->in_streams[n].in = NULL;
                continue;
            }
            /* move from last to the first */
            li = li->next;
            fli = li;
            lo = ngx_rtmp_alloc_in_buf(s);
            if (lo == NULL) {
                return NGX_ERROR;
            }
            flo = lo;
            for ( ;; ) {
                bi = li->buf;
                bo = lo->buf;

                if (bo->end - bo->last >= bi->last - bi->pos) {
                    bo->last = ngx_cpymem(bo->last, bi->pos,
                            bi->last - bi->pos);
                    li = li->next;
                    if (li == fli)  {
                        lo->next = flo;
                        s->in_streams[n].in = lo;
                        break;
                    }
                    continue;
                }

                bi->pos += (ngx_cpymem(bo->last, bi->pos,
                            bo->end - bo->last) - bo->last);
                lo->next = ngx_rtmp_alloc_in_buf(s);
                lo = lo->next;
                if (lo == NULL) {
                    return NGX_ERROR;
                }
            }
        }
    }

    return NGX_OK;
}
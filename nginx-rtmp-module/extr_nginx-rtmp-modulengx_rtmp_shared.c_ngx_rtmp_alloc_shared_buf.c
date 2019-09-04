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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {size_t chunk_size; int /*<<< orphan*/  pool; TYPE_2__* free; } ;
typedef  TYPE_1__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_8__ {TYPE_3__* buf; struct TYPE_8__* next; } ;
typedef  TYPE_2__ ngx_chain_t ;
struct TYPE_9__ {int memory; int /*<<< orphan*/ * start; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * end; } ;
typedef  TYPE_3__ ngx_buf_t ;

/* Variables and functions */
 size_t NGX_RTMP_MAX_CHUNK_HEADER ; 
 scalar_t__ NGX_RTMP_REFCOUNT_BYTES ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_rtmp_ref_set (TYPE_2__*,int) ; 

ngx_chain_t *
ngx_rtmp_alloc_shared_buf(ngx_rtmp_core_srv_conf_t *cscf)
{
    u_char                     *p;
    ngx_chain_t                *out;
    ngx_buf_t                  *b;
    size_t                      size;

    if (cscf->free) {
        out = cscf->free;
        cscf->free = out->next;

    } else {

        size = cscf->chunk_size + NGX_RTMP_MAX_CHUNK_HEADER;

        p = ngx_pcalloc(cscf->pool, NGX_RTMP_REFCOUNT_BYTES
                + sizeof(ngx_chain_t)
                + sizeof(ngx_buf_t)
                + size);
        if (p == NULL) {
            return NULL;
        }

        p += NGX_RTMP_REFCOUNT_BYTES;
        out = (ngx_chain_t *)p;

        p += sizeof(ngx_chain_t);
        out->buf = (ngx_buf_t *)p;

        p += sizeof(ngx_buf_t);
        out->buf->start = p;
        out->buf->end = p + size;
    }

    out->next = NULL;
    b = out->buf;
    b->pos = b->last = b->start + NGX_RTMP_MAX_CHUNK_HEADER;
    b->memory = 1;

    /* buffer has refcount =1 when created! */
    ngx_rtmp_ref_set(out, 1);

    return out;
}
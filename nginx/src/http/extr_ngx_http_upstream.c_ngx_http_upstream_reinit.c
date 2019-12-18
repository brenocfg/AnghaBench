#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_22__ {int /*<<< orphan*/  pos; int /*<<< orphan*/  last; int /*<<< orphan*/  start; } ;
struct TYPE_20__ {int /*<<< orphan*/ * busy; int /*<<< orphan*/ * in; TYPE_3__* buf; TYPE_14__* free; } ;
struct TYPE_15__ {int content_length_n; int last_modified_time; int /*<<< orphan*/  trailers; int /*<<< orphan*/  headers; } ;
struct TYPE_23__ {scalar_t__ (* reinit_request ) (TYPE_8__*) ;TYPE_6__ buffer; TYPE_4__ output; TYPE_9__* request_bufs; TYPE_11__ headers_in; scalar_t__ upgrade; scalar_t__ keepalive; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_headers_in_t ;
struct TYPE_24__ {TYPE_5__* cache; int /*<<< orphan*/  pool; struct TYPE_24__* main; TYPE_2__* request_body; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_25__ {TYPE_1__* buf; struct TYPE_25__* next; } ;
typedef  TYPE_9__ ngx_chain_t ;
struct TYPE_21__ {scalar_t__ header_start; } ;
struct TYPE_19__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;
struct TYPE_18__ {scalar_t__ temp_file; } ;
struct TYPE_17__ {scalar_t__ file_last; scalar_t__ file_pos; scalar_t__ in_file; int /*<<< orphan*/  start; int /*<<< orphan*/  pos; } ;
struct TYPE_16__ {int /*<<< orphan*/ * next; TYPE_3__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 TYPE_14__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_11__*,int) ; 
 scalar_t__ stub1 (TYPE_8__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_reinit(ngx_http_request_t *r, ngx_http_upstream_t *u)
{
    off_t         file_pos;
    ngx_chain_t  *cl;

    if (u->reinit_request(r) != NGX_OK) {
        return NGX_ERROR;
    }

    u->keepalive = 0;
    u->upgrade = 0;

    ngx_memzero(&u->headers_in, sizeof(ngx_http_upstream_headers_in_t));
    u->headers_in.content_length_n = -1;
    u->headers_in.last_modified_time = -1;

    if (ngx_list_init(&u->headers_in.headers, r->pool, 8,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    if (ngx_list_init(&u->headers_in.trailers, r->pool, 2,
                      sizeof(ngx_table_elt_t))
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    /* reinit the request chain */

    file_pos = 0;

    for (cl = u->request_bufs; cl; cl = cl->next) {
        cl->buf->pos = cl->buf->start;

        /* there is at most one file */

        if (cl->buf->in_file) {
            cl->buf->file_pos = file_pos;
            file_pos = cl->buf->file_last;
        }
    }

    /* reinit the subrequest's ngx_output_chain() context */

    if (r->request_body && r->request_body->temp_file
        && r != r->main && u->output.buf)
    {
        u->output.free = ngx_alloc_chain_link(r->pool);
        if (u->output.free == NULL) {
            return NGX_ERROR;
        }

        u->output.free->buf = u->output.buf;
        u->output.free->next = NULL;

        u->output.buf->pos = u->output.buf->start;
        u->output.buf->last = u->output.buf->start;
    }

    u->output.buf = NULL;
    u->output.in = NULL;
    u->output.busy = NULL;

    /* reinit u->buffer */

    u->buffer.pos = u->buffer.start;

#if (NGX_HTTP_CACHE)

    if (r->cache) {
        u->buffer.pos += r->cache->header_start;
    }

#endif

    u->buffer.last = u->buffer.pos;

    return NGX_OK;
}
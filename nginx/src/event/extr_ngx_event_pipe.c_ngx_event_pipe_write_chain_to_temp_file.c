#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int ngx_uint_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {scalar_t__ temp_file_write_size; scalar_t__ max_temp_file_size; int /*<<< orphan*/  pool; TYPE_3__* free; TYPE_3__* free_raw_bufs; TYPE_5__* temp_file; int /*<<< orphan*/  tag; TYPE_3__* out; TYPE_4__* buf_to_file; int /*<<< orphan*/  thread_task; TYPE_3__* writing; int /*<<< orphan*/  thread_ctx; scalar_t__ thread_handler; TYPE_3__* in; TYPE_3__** last_in; int /*<<< orphan*/  log; int /*<<< orphan*/  cacheable; scalar_t__ aio; } ;
typedef  TYPE_2__ ngx_event_pipe_t ;
struct TYPE_15__ {struct TYPE_15__* next; TYPE_4__* buf; } ;
typedef  TYPE_3__ ngx_chain_t ;
struct TYPE_16__ {scalar_t__ last; scalar_t__ pos; int last_shadow; scalar_t__ start; scalar_t__ file_last; scalar_t__ file_pos; int in_file; int temp_file; struct TYPE_16__* shadow; TYPE_1__* file; int /*<<< orphan*/  tag; } ;
typedef  TYPE_4__ ngx_buf_t ;
struct TYPE_13__ {int /*<<< orphan*/  thread_task; int /*<<< orphan*/  thread_ctx; scalar_t__ thread_handler; } ;
struct TYPE_17__ {scalar_t__ offset; int thread_write; TYPE_1__ file; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_chain_get_free_buf (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  ngx_event_pipe_remove_shadow_links (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 scalar_t__ ngx_write_chain_to_temp_file (TYPE_5__*,TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_event_pipe_write_chain_to_temp_file(ngx_event_pipe_t *p)
{
    ssize_t       size, bsize, n;
    ngx_buf_t    *b;
    ngx_uint_t    prev_last_shadow;
    ngx_chain_t  *cl, *tl, *next, *out, **ll, **last_out, **last_free;

#if (NGX_THREADS)

    if (p->writing) {

        if (p->aio) {
            return NGX_AGAIN;
        }

        out = p->writing;
        p->writing = NULL;

        n = ngx_write_chain_to_temp_file(p->temp_file, NULL);

        if (n == NGX_ERROR) {
            return NGX_ABORT;
        }

        goto done;
    }

#endif

    if (p->buf_to_file) {
        out = ngx_alloc_chain_link(p->pool);
        if (out == NULL) {
            return NGX_ABORT;
        }

        out->buf = p->buf_to_file;
        out->next = p->in;

    } else {
        out = p->in;
    }

    if (!p->cacheable) {

        size = 0;
        cl = out;
        ll = NULL;
        prev_last_shadow = 1;

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe offset: %O", p->temp_file->offset);

        do {
            bsize = cl->buf->last - cl->buf->pos;

            ngx_log_debug4(NGX_LOG_DEBUG_EVENT, p->log, 0,
                           "pipe buf ls:%d %p, pos %p, size: %z",
                           cl->buf->last_shadow, cl->buf->start,
                           cl->buf->pos, bsize);

            if (prev_last_shadow
                && ((size + bsize > p->temp_file_write_size)
                    || (p->temp_file->offset + size + bsize
                        > p->max_temp_file_size)))
            {
                break;
            }

            prev_last_shadow = cl->buf->last_shadow;

            size += bsize;
            ll = &cl->next;
            cl = cl->next;

        } while (cl);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0, "size: %z", size);

        if (ll == NULL) {
            return NGX_BUSY;
        }

        if (cl) {
            p->in = cl;
            *ll = NULL;

        } else {
            p->in = NULL;
            p->last_in = &p->in;
        }

    } else {
        p->in = NULL;
        p->last_in = &p->in;
    }

#if (NGX_THREADS)
    if (p->thread_handler) {
        p->temp_file->thread_write = 1;
        p->temp_file->file.thread_task = p->thread_task;
        p->temp_file->file.thread_handler = p->thread_handler;
        p->temp_file->file.thread_ctx = p->thread_ctx;
    }
#endif

    n = ngx_write_chain_to_temp_file(p->temp_file, out);

    if (n == NGX_ERROR) {
        return NGX_ABORT;
    }

#if (NGX_THREADS)

    if (n == NGX_AGAIN) {
        p->writing = out;
        p->thread_task = p->temp_file->file.thread_task;
        return NGX_AGAIN;
    }

done:

#endif

    if (p->buf_to_file) {
        p->temp_file->offset = p->buf_to_file->last - p->buf_to_file->pos;
        n -= p->buf_to_file->last - p->buf_to_file->pos;
        p->buf_to_file = NULL;
        out = out->next;
    }

    if (n > 0) {
        /* update previous buffer or add new buffer */

        if (p->out) {
            for (cl = p->out; cl->next; cl = cl->next) { /* void */ }

            b = cl->buf;

            if (b->file_last == p->temp_file->offset) {
                p->temp_file->offset += n;
                b->file_last = p->temp_file->offset;
                goto free;
            }

            last_out = &cl->next;

        } else {
            last_out = &p->out;
        }

        cl = ngx_chain_get_free_buf(p->pool, &p->free);
        if (cl == NULL) {
            return NGX_ABORT;
        }

        b = cl->buf;

        ngx_memzero(b, sizeof(ngx_buf_t));

        b->tag = p->tag;

        b->file = &p->temp_file->file;
        b->file_pos = p->temp_file->offset;
        p->temp_file->offset += n;
        b->file_last = p->temp_file->offset;

        b->in_file = 1;
        b->temp_file = 1;

        *last_out = cl;
    }

free:

    for (last_free = &p->free_raw_bufs;
         *last_free != NULL;
         last_free = &(*last_free)->next)
    {
        /* void */
    }

    for (cl = out; cl; cl = next) {
        next = cl->next;

        cl->next = p->free;
        p->free = cl;

        b = cl->buf;

        if (b->last_shadow) {

            tl = ngx_alloc_chain_link(p->pool);
            if (tl == NULL) {
                return NGX_ABORT;
            }

            tl->buf = b->shadow;
            tl->next = NULL;

            *last_free = tl;
            last_free = &tl->next;

            b->shadow->pos = b->shadow->start;
            b->shadow->last = b->shadow->start;

            ngx_event_pipe_remove_shadow_links(b->shadow);
        }
    }

    return NGX_OK;
}
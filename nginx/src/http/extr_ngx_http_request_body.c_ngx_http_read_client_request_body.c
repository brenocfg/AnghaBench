#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int off_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {scalar_t__ content_length_n; int /*<<< orphan*/  chunked; } ;
struct TYPE_25__ {int reading_body; int /*<<< orphan*/  count; struct TYPE_25__* main; void* read_event_handler; scalar_t__ request_body_no_buffering; void* write_event_handler; int /*<<< orphan*/  pool; scalar_t__ request_body_in_single_buf; TYPE_3__ headers_in; TYPE_2__* connection; TYPE_1__* header_in; int /*<<< orphan*/  request_length; scalar_t__ stream; TYPE_5__* request_body; scalar_t__ discard_body; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_26__ {int rest; TYPE_9__* buf; int /*<<< orphan*/  (* post_handler ) (TYPE_4__*) ;} ;
typedef  TYPE_5__ ngx_http_request_body_t ;
struct TYPE_27__ {int client_body_buffer_size; } ;
typedef  TYPE_6__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  (* ngx_http_client_body_handler_pt ) (TYPE_4__*) ;
struct TYPE_28__ {int /*<<< orphan*/ * next; TYPE_1__* buf; } ;
typedef  TYPE_8__ ngx_chain_t ;
struct TYPE_29__ {int temporary; size_t start; size_t pos; size_t last; size_t end; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
struct TYPE_22__ {size_t last; size_t pos; size_t end; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_9__* ngx_calloc_buf (int /*<<< orphan*/ ) ; 
 TYPE_9__* ngx_create_temp_buf (int /*<<< orphan*/ ,int) ; 
 void* ngx_http_block_reading ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 scalar_t__ ngx_http_do_read_client_request_body (TYPE_4__*) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_read_client_request_body_handler ; 
 scalar_t__ ngx_http_request_body_filter (TYPE_4__*,TYPE_8__*) ; 
 void* ngx_http_request_empty_handler ; 
 scalar_t__ ngx_http_test_expect (TYPE_4__*) ; 
 scalar_t__ ngx_http_v2_read_request_body (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_read_client_request_body(ngx_http_request_t *r,
    ngx_http_client_body_handler_pt post_handler)
{
    size_t                     preread;
    ssize_t                    size;
    ngx_int_t                  rc;
    ngx_buf_t                 *b;
    ngx_chain_t                out;
    ngx_http_request_body_t   *rb;
    ngx_http_core_loc_conf_t  *clcf;

    r->main->count++;

    if (r != r->main || r->request_body || r->discard_body) {
        r->request_body_no_buffering = 0;
        post_handler(r);
        return NGX_OK;
    }

    if (ngx_http_test_expect(r) != NGX_OK) {
        rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        goto done;
    }

    rb = ngx_pcalloc(r->pool, sizeof(ngx_http_request_body_t));
    if (rb == NULL) {
        rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        goto done;
    }

    /*
     * set by ngx_pcalloc():
     *
     *     rb->bufs = NULL;
     *     rb->buf = NULL;
     *     rb->free = NULL;
     *     rb->busy = NULL;
     *     rb->chunked = NULL;
     */

    rb->rest = -1;
    rb->post_handler = post_handler;

    r->request_body = rb;

    if (r->headers_in.content_length_n < 0 && !r->headers_in.chunked) {
        r->request_body_no_buffering = 0;
        post_handler(r);
        return NGX_OK;
    }

#if (NGX_HTTP_V2)
    if (r->stream) {
        rc = ngx_http_v2_read_request_body(r);
        goto done;
    }
#endif

    preread = r->header_in->last - r->header_in->pos;

    if (preread) {

        /* there is the pre-read part of the request body */

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http client request body preread %uz", preread);

        out.buf = r->header_in;
        out.next = NULL;

        rc = ngx_http_request_body_filter(r, &out);

        if (rc != NGX_OK) {
            goto done;
        }

        r->request_length += preread - (r->header_in->last - r->header_in->pos);

        if (!r->headers_in.chunked
            && rb->rest > 0
            && rb->rest <= (off_t) (r->header_in->end - r->header_in->last))
        {
            /* the whole request body may be placed in r->header_in */

            b = ngx_calloc_buf(r->pool);
            if (b == NULL) {
                rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
                goto done;
            }

            b->temporary = 1;
            b->start = r->header_in->pos;
            b->pos = r->header_in->pos;
            b->last = r->header_in->last;
            b->end = r->header_in->end;

            rb->buf = b;

            r->read_event_handler = ngx_http_read_client_request_body_handler;
            r->write_event_handler = ngx_http_request_empty_handler;

            rc = ngx_http_do_read_client_request_body(r);
            goto done;
        }

    } else {
        /* set rb->rest */

        if (ngx_http_request_body_filter(r, NULL) != NGX_OK) {
            rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
            goto done;
        }
    }

    if (rb->rest == 0) {
        /* the whole request body was pre-read */
        r->request_body_no_buffering = 0;
        post_handler(r);
        return NGX_OK;
    }

    if (rb->rest < 0) {
        ngx_log_error(NGX_LOG_ALERT, r->connection->log, 0,
                      "negative request body rest");
        rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        goto done;
    }

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    size = clcf->client_body_buffer_size;
    size += size >> 2;

    /* TODO: honor r->request_body_in_single_buf */

    if (!r->headers_in.chunked && rb->rest < size) {
        size = (ssize_t) rb->rest;

        if (r->request_body_in_single_buf) {
            size += preread;
        }

    } else {
        size = clcf->client_body_buffer_size;
    }

    rb->buf = ngx_create_temp_buf(r->pool, size);
    if (rb->buf == NULL) {
        rc = NGX_HTTP_INTERNAL_SERVER_ERROR;
        goto done;
    }

    r->read_event_handler = ngx_http_read_client_request_body_handler;
    r->write_event_handler = ngx_http_request_empty_handler;

    rc = ngx_http_do_read_client_request_body(r);

done:

    if (r->request_body_no_buffering
        && (rc == NGX_OK || rc == NGX_AGAIN))
    {
        if (rc == NGX_OK) {
            r->request_body_no_buffering = 0;

        } else {
            /* rc == NGX_AGAIN */
            r->reading_body = 1;
        }

        r->read_event_handler = ngx_http_block_reading;
        post_handler(r);
    }

    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        r->main->count--;
    }

    return rc;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {scalar_t__ content_length_n; scalar_t__ chunked; } ;
struct TYPE_16__ {int discard_body; int /*<<< orphan*/  count; int /*<<< orphan*/  read_event_handler; scalar_t__ lingering_close; TYPE_3__ headers_in; TYPE_9__* header_in; TYPE_2__* connection; TYPE_1__* stream; scalar_t__ request_body; struct TYPE_16__* main; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {scalar_t__ timer_set; int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_event_t ;
struct TYPE_18__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_14__ {TYPE_5__* read; } ;
struct TYPE_13__ {int skip_data; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_5__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_discard_request_body_filter (TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_discarded_request_body_handler ; 
 scalar_t__ ngx_http_read_discarded_request_body (TYPE_4__*) ; 
 scalar_t__ ngx_http_test_expect (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_http_discard_request_body(ngx_http_request_t *r)
{
    ssize_t       size;
    ngx_int_t     rc;
    ngx_event_t  *rev;

    if (r != r->main || r->discard_body || r->request_body) {
        return NGX_OK;
    }

#if (NGX_HTTP_V2)
    if (r->stream) {
        r->stream->skip_data = 1;
        return NGX_OK;
    }
#endif

    if (ngx_http_test_expect(r) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    rev = r->connection->read;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, rev->log, 0, "http set discard body");

    if (rev->timer_set) {
        ngx_del_timer(rev);
    }

    if (r->headers_in.content_length_n <= 0 && !r->headers_in.chunked) {
        return NGX_OK;
    }

    size = r->header_in->last - r->header_in->pos;

    if (size || r->headers_in.chunked) {
        rc = ngx_http_discard_request_body_filter(r, r->header_in);

        if (rc != NGX_OK) {
            return rc;
        }

        if (r->headers_in.content_length_n == 0) {
            return NGX_OK;
        }
    }

    rc = ngx_http_read_discarded_request_body(r);

    if (rc == NGX_OK) {
        r->lingering_close = 0;
        return NGX_OK;
    }

    if (rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return rc;
    }

    /* rc == NGX_AGAIN */

    r->read_event_handler = ngx_http_discarded_request_body_handler;

    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    r->count++;
    r->discard_body = 1;

    return NGX_OK;
}
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
struct TYPE_15__ {int /*<<< orphan*/  payload_bytes; } ;
typedef  TYPE_3__ ngx_http_v2_connection_t ;
struct TYPE_13__ {int content_length_n; int chunked; } ;
struct TYPE_16__ {scalar_t__ request_length; TYPE_2__* stream; TYPE_1__ headers_in; TYPE_5__* connection; int /*<<< orphan*/  http_state; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_14__ {int skip_data; TYPE_3__* connection; scalar_t__ in_closed; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_BAD_REQUEST ; 
 int /*<<< orphan*/  NGX_HTTP_PROCESS_REQUEST_STATE ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_process_request (TYPE_4__*) ; 
 scalar_t__ ngx_http_process_request_header (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_5__*) ; 
 scalar_t__ ngx_http_v2_construct_cookie_header (TYPE_4__*) ; 
 scalar_t__ ngx_http_v2_construct_request_line (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_v2_run_request(ngx_http_request_t *r)
{
    ngx_connection_t          *fc;
    ngx_http_v2_connection_t  *h2c;

    fc = r->connection;

    if (ngx_http_v2_construct_request_line(r) != NGX_OK) {
        goto failed;
    }

    if (ngx_http_v2_construct_cookie_header(r) != NGX_OK) {
        goto failed;
    }

    r->http_state = NGX_HTTP_PROCESS_REQUEST_STATE;

    if (ngx_http_process_request_header(r) != NGX_OK) {
        goto failed;
    }

    if (r->headers_in.content_length_n > 0 && r->stream->in_closed) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client prematurely closed stream");

        r->stream->skip_data = 1;

        ngx_http_finalize_request(r, NGX_HTTP_BAD_REQUEST);
        goto failed;
    }

    if (r->headers_in.content_length_n == -1 && !r->stream->in_closed) {
        r->headers_in.chunked = 1;
    }

    h2c = r->stream->connection;

    h2c->payload_bytes += r->request_length;

    ngx_http_process_request(r);

failed:

    ngx_http_run_posted_requests(fc);
}
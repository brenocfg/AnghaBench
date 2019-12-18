#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_22__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
struct TYPE_32__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_5__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_31__ {int /*<<< orphan*/  headers; TYPE_5__ server; } ;
struct TYPE_30__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_29__ {scalar_t__ data; scalar_t__ len; } ;
struct TYPE_27__ {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_33__ {scalar_t__ request_end; scalar_t__ request_start; scalar_t__ request_length; scalar_t__ method_end; scalar_t__ host_end; scalar_t__ host_start; scalar_t__ http_version; TYPE_11__ request_line; TYPE_22__* header_in; int /*<<< orphan*/  pool; TYPE_4__ headers_in; scalar_t__ schema_start; TYPE_3__ schema; scalar_t__ schema_end; TYPE_2__ http_protocol; TYPE_1__ method_name; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_34__ {int /*<<< orphan*/  (* handler ) (TYPE_7__*) ;scalar_t__ timedout; int /*<<< orphan*/  log; TYPE_8__* data; } ;
typedef  TYPE_7__ ngx_event_t ;
struct TYPE_35__ {int timedout; TYPE_9__* log; TYPE_6__* data; } ;
typedef  TYPE_8__ ngx_connection_t ;
struct TYPE_36__ {char* action; } ;
struct TYPE_28__ {scalar_t__ pos; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_REQUEST ; 
 scalar_t__ NGX_HTTP_CLIENT_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 scalar_t__ NGX_HTTP_PARSE_INVALID_VERSION ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_TIME_OUT ; 
 int /*<<< orphan*/  NGX_HTTP_REQUEST_URI_TOO_LARGE ; 
 scalar_t__ NGX_HTTP_VERSION_10 ; 
 int /*<<< orphan*/  NGX_HTTP_VERSION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_alloc_large_header_buffer (TYPE_6__*,int) ; 
 char** ngx_http_client_errors ; 
 int /*<<< orphan*/  ngx_http_close_request (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_parse_request_line (TYPE_6__*,TYPE_22__*) ; 
 int /*<<< orphan*/  ngx_http_process_request (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_process_request_headers (TYPE_7__*) ; 
 scalar_t__ ngx_http_process_request_uri (TYPE_6__*) ; 
 scalar_t__ ngx_http_read_request_header (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_8__*) ; 
 scalar_t__ ngx_http_set_virtual_server (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ ngx_http_validate_host (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,TYPE_11__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_process_request_line(ngx_event_t *rev)
{
    ssize_t              n;
    ngx_int_t            rc, rv;
    ngx_str_t            host;
    ngx_connection_t    *c;
    ngx_http_request_t  *r;

    c = rev->data;
    r = c->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, rev->log, 0,
                   "http process request line");

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        c->timedout = 1;
        ngx_http_close_request(r, NGX_HTTP_REQUEST_TIME_OUT);
        return;
    }

    rc = NGX_AGAIN;

    for ( ;; ) {

        if (rc == NGX_AGAIN) {
            n = ngx_http_read_request_header(r);

            if (n == NGX_AGAIN || n == NGX_ERROR) {
                break;
            }
        }

        rc = ngx_http_parse_request_line(r, r->header_in);

        if (rc == NGX_OK) {

            /* the request line has been parsed successfully */

            r->request_line.len = r->request_end - r->request_start;
            r->request_line.data = r->request_start;
            r->request_length = r->header_in->pos - r->request_start;

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                           "http request line: \"%V\"", &r->request_line);

            r->method_name.len = r->method_end - r->request_start + 1;
            r->method_name.data = r->request_line.data;

            if (r->http_protocol.data) {
                r->http_protocol.len = r->request_end - r->http_protocol.data;
            }

            if (ngx_http_process_request_uri(r) != NGX_OK) {
                break;
            }

            if (r->schema_end) {
                r->schema.len = r->schema_end - r->schema_start;
                r->schema.data = r->schema_start;
            }

            if (r->host_end) {

                host.len = r->host_end - r->host_start;
                host.data = r->host_start;

                rc = ngx_http_validate_host(&host, r->pool, 0);

                if (rc == NGX_DECLINED) {
                    ngx_log_error(NGX_LOG_INFO, c->log, 0,
                                  "client sent invalid host in request line");
                    ngx_http_finalize_request(r, NGX_HTTP_BAD_REQUEST);
                    break;
                }

                if (rc == NGX_ERROR) {
                    ngx_http_close_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
                    break;
                }

                if (ngx_http_set_virtual_server(r, &host) == NGX_ERROR) {
                    break;
                }

                r->headers_in.server = host;
            }

            if (r->http_version < NGX_HTTP_VERSION_10) {

                if (r->headers_in.server.len == 0
                    && ngx_http_set_virtual_server(r, &r->headers_in.server)
                       == NGX_ERROR)
                {
                    break;
                }

                ngx_http_process_request(r);
                break;
            }


            if (ngx_list_init(&r->headers_in.headers, r->pool, 20,
                              sizeof(ngx_table_elt_t))
                != NGX_OK)
            {
                ngx_http_close_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
                break;
            }

            c->log->action = "reading client request headers";

            rev->handler = ngx_http_process_request_headers;
            ngx_http_process_request_headers(rev);

            break;
        }

        if (rc != NGX_AGAIN) {

            /* there was error while a request line parsing */

            ngx_log_error(NGX_LOG_INFO, c->log, 0,
                          ngx_http_client_errors[rc - NGX_HTTP_CLIENT_ERROR]);

            if (rc == NGX_HTTP_PARSE_INVALID_VERSION) {
                ngx_http_finalize_request(r, NGX_HTTP_VERSION_NOT_SUPPORTED);

            } else {
                ngx_http_finalize_request(r, NGX_HTTP_BAD_REQUEST);
            }

            break;
        }

        /* NGX_AGAIN: a request line parsing is still incomplete */

        if (r->header_in->pos == r->header_in->end) {

            rv = ngx_http_alloc_large_header_buffer(r, 1);

            if (rv == NGX_ERROR) {
                ngx_http_close_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
                break;
            }

            if (rv == NGX_DECLINED) {
                r->request_line.len = r->header_in->end - r->request_start;
                r->request_line.data = r->request_start;

                ngx_log_error(NGX_LOG_INFO, c->log, 0,
                              "client sent too long URI");
                ngx_http_finalize_request(r, NGX_HTTP_REQUEST_URI_TOO_LARGE);
                break;
            }
        }
    }

    ngx_http_run_posted_requests(c);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {scalar_t__ status; int content_length_n; } ;
struct TYPE_11__ {scalar_t__ method; scalar_t__ http_version; int chunked; scalar_t__ keepalive; TYPE_1__ headers_out; int /*<<< orphan*/  pool; scalar_t__ expect_trailers; struct TYPE_11__* main; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {scalar_t__ chunked_transfer_encoding; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_chunked_filter_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_HEAD ; 
 scalar_t__ NGX_HTTP_NOT_MODIFIED ; 
 scalar_t__ NGX_HTTP_NO_CONTENT ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_VERSION_11 ; 
 int /*<<< orphan*/  ngx_http_chunked_filter_module ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_chunked_header_filter(ngx_http_request_t *r)
{
    ngx_http_core_loc_conf_t       *clcf;
    ngx_http_chunked_filter_ctx_t  *ctx;

    if (r->headers_out.status == NGX_HTTP_NOT_MODIFIED
        || r->headers_out.status == NGX_HTTP_NO_CONTENT
        || r->headers_out.status < NGX_HTTP_OK
        || r != r->main
        || r->method == NGX_HTTP_HEAD)
    {
        return ngx_http_next_header_filter(r);
    }

    if (r->headers_out.content_length_n == -1
        || r->expect_trailers)
    {
        clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

        if (r->http_version >= NGX_HTTP_VERSION_11
            && clcf->chunked_transfer_encoding)
        {
            if (r->expect_trailers) {
                ngx_http_clear_content_length(r);
            }

            r->chunked = 1;

            ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_chunked_filter_ctx_t));
            if (ctx == NULL) {
                return NGX_ERROR;
            }

            ngx_http_set_ctx(r, ctx, ngx_http_chunked_filter_module);

        } else if (r->headers_out.content_length_n == -1) {
            r->keepalive = 0;
        }
    }

    return ngx_http_next_header_filter(r);
}
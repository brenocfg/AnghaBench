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
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_26__ {TYPE_1__ value; } ;
typedef  TYPE_6__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_27__ {int size; } ;
typedef  TYPE_7__ ngx_http_slice_loc_conf_t ;
struct TYPE_28__ {int start; int active; int end; TYPE_1__ etag; } ;
typedef  TYPE_8__ ngx_http_slice_ctx_t ;
struct TYPE_29__ {int complete_length; scalar_t__ start; scalar_t__ end; } ;
typedef  TYPE_9__ ngx_http_slice_content_range_t ;
struct TYPE_23__ {scalar_t__ len; } ;
struct TYPE_25__ {scalar_t__ status; int content_length_n; int content_offset; TYPE_4__* content_range; TYPE_3__ status_line; TYPE_6__* etag; } ;
struct TYPE_20__ {int allow_ranges; int subrequest_ranges; int single_range; int preserve_body; TYPE_5__ headers_out; struct TYPE_20__* main; TYPE_2__* connection; } ;
typedef  TYPE_10__ ngx_http_request_t ;
struct TYPE_24__ {scalar_t__ hash; } ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_OK ; 
 scalar_t__ NGX_HTTP_PARTIAL_CONTENT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_8__* ngx_http_get_module_ctx (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_slice_filter_module ; 
 scalar_t__ ngx_http_slice_parse_content_range (TYPE_10__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_min (scalar_t__,int) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_http_slice_header_filter(ngx_http_request_t *r)
{
    off_t                            end;
    ngx_int_t                        rc;
    ngx_table_elt_t                 *h;
    ngx_http_slice_ctx_t            *ctx;
    ngx_http_slice_loc_conf_t       *slcf;
    ngx_http_slice_content_range_t   cr;

    ctx = ngx_http_get_module_ctx(r, ngx_http_slice_filter_module);
    if (ctx == NULL) {
        return ngx_http_next_header_filter(r);
    }

    if (r->headers_out.status != NGX_HTTP_PARTIAL_CONTENT) {
        if (r == r->main) {
            ngx_http_set_ctx(r, NULL, ngx_http_slice_filter_module);
            return ngx_http_next_header_filter(r);
        }

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "unexpected status code %ui in slice response",
                      r->headers_out.status);
        return NGX_ERROR;
    }

    h = r->headers_out.etag;

    if (ctx->etag.len) {
        if (h == NULL
            || h->value.len != ctx->etag.len
            || ngx_strncmp(h->value.data, ctx->etag.data, ctx->etag.len)
               != 0)
        {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "etag mismatch in slice response");
            return NGX_ERROR;
        }
    }

    if (h) {
        ctx->etag = h->value;
    }

    if (ngx_http_slice_parse_content_range(r, &cr) != NGX_OK) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "invalid range in slice response");
        return NGX_ERROR;
    }

    if (cr.complete_length == -1) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "no complete length in slice response");
        return NGX_ERROR;
    }

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http slice response range: %O-%O/%O",
                   cr.start, cr.end, cr.complete_length);

    slcf = ngx_http_get_module_loc_conf(r, ngx_http_slice_filter_module);

    end = ngx_min(cr.start + (off_t) slcf->size, cr.complete_length);

    if (cr.start != ctx->start || cr.end != end) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "unexpected range in slice response: %O-%O",
                      cr.start, cr.end);
        return NGX_ERROR;
    }

    ctx->start = end;
    ctx->active = 1;

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.status_line.len = 0;
    r->headers_out.content_length_n = cr.complete_length;
    r->headers_out.content_offset = cr.start;
    r->headers_out.content_range->hash = 0;
    r->headers_out.content_range = NULL;

    r->allow_ranges = 1;
    r->subrequest_ranges = 1;
    r->single_range = 1;

    rc = ngx_http_next_header_filter(r);

    if (r != r->main) {
        return rc;
    }

    r->preserve_body = 1;

    if (r->headers_out.status == NGX_HTTP_PARTIAL_CONTENT) {
        if (ctx->start + (off_t) slcf->size <= r->headers_out.content_offset) {
            ctx->start = slcf->size
                         * (r->headers_out.content_offset / slcf->size);
        }

        ctx->end = r->headers_out.content_offset
                   + r->headers_out.content_length_n;

    } else {
        ctx->end = cr.complete_length;
    }

    return rc;
}
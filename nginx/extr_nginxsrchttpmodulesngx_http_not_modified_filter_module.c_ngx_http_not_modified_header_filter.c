#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {scalar_t__ len; } ;
struct TYPE_16__ {scalar_t__ len; } ;
struct TYPE_19__ {scalar_t__ status; TYPE_4__* content_encoding; TYPE_3__ content_type; TYPE_2__ status_line; } ;
struct TYPE_15__ {scalar_t__ if_none_match; scalar_t__ if_modified_since; scalar_t__ if_match; scalar_t__ if_unmodified_since; } ;
struct TYPE_20__ {TYPE_5__ headers_out; TYPE_1__ headers_in; scalar_t__ disable_not_modified; struct TYPE_20__* main; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_18__ {scalar_t__ hash; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_NOT_MODIFIED ; 
 scalar_t__ NGX_HTTP_OK ; 
 int /*<<< orphan*/  NGX_HTTP_PRECONDITION_FAILED ; 
 int /*<<< orphan*/  ngx_http_clear_accept_ranges (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_filter_finalize_request (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_test_if_match (TYPE_6__*,scalar_t__,int) ; 
 scalar_t__ ngx_http_test_if_modified (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_test_if_unmodified (TYPE_6__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_not_modified_header_filter(ngx_http_request_t *r)
{
    if (r->headers_out.status != NGX_HTTP_OK
        || r != r->main
        || r->disable_not_modified)
    {
        return ngx_http_next_header_filter(r);
    }

    if (r->headers_in.if_unmodified_since
        && !ngx_http_test_if_unmodified(r))
    {
        return ngx_http_filter_finalize_request(r, NULL,
                                                NGX_HTTP_PRECONDITION_FAILED);
    }

    if (r->headers_in.if_match
        && !ngx_http_test_if_match(r, r->headers_in.if_match, 0))
    {
        return ngx_http_filter_finalize_request(r, NULL,
                                                NGX_HTTP_PRECONDITION_FAILED);
    }

    if (r->headers_in.if_modified_since || r->headers_in.if_none_match) {

        if (r->headers_in.if_modified_since
            && ngx_http_test_if_modified(r))
        {
            return ngx_http_next_header_filter(r);
        }

        if (r->headers_in.if_none_match
            && !ngx_http_test_if_match(r, r->headers_in.if_none_match, 1))
        {
            return ngx_http_next_header_filter(r);
        }

        /* not modified */

        r->headers_out.status = NGX_HTTP_NOT_MODIFIED;
        r->headers_out.status_line.len = 0;
        r->headers_out.content_type.len = 0;
        ngx_http_clear_content_length(r);
        ngx_http_clear_accept_ranges(r);

        if (r->headers_out.content_encoding) {
            r->headers_out.content_encoding->hash = 0;
            r->headers_out.content_encoding = NULL;
        }

        return ngx_http_next_header_filter(r);
    }

    return ngx_http_next_header_filter(r);
}
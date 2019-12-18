#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int status; } ;
struct TYPE_19__ {int expect_trailers; TYPE_1__ headers_out; struct TYPE_19__* main; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_20__ {scalar_t__ expires; TYPE_3__* trailers; TYPE_2__* headers; } ;
typedef  TYPE_5__ ngx_http_headers_conf_t ;
struct TYPE_21__ {scalar_t__ (* handler ) (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  always; int /*<<< orphan*/  value; } ;
typedef  TYPE_6__ ngx_http_header_val_t ;
struct TYPE_18__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_17__ {size_t nelts; TYPE_6__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
#define  NGX_HTTP_CREATED 137 
 scalar_t__ NGX_HTTP_EXPIRES_OFF ; 
#define  NGX_HTTP_MOVED_PERMANENTLY 136 
#define  NGX_HTTP_MOVED_TEMPORARILY 135 
#define  NGX_HTTP_NOT_MODIFIED 134 
#define  NGX_HTTP_NO_CONTENT 133 
#define  NGX_HTTP_OK 132 
#define  NGX_HTTP_PARTIAL_CONTENT 131 
#define  NGX_HTTP_PERMANENT_REDIRECT 130 
#define  NGX_HTTP_SEE_OTHER 129 
#define  NGX_HTTP_TEMPORARY_REDIRECT 128 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_headers_filter_module ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_4__*) ; 
 scalar_t__ ngx_http_set_expires (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ stub1 (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_headers_filter(ngx_http_request_t *r)
{
    ngx_str_t                 value;
    ngx_uint_t                i, safe_status;
    ngx_http_header_val_t    *h;
    ngx_http_headers_conf_t  *conf;

    if (r != r->main) {
        return ngx_http_next_header_filter(r);
    }

    conf = ngx_http_get_module_loc_conf(r, ngx_http_headers_filter_module);

    if (conf->expires == NGX_HTTP_EXPIRES_OFF
        && conf->headers == NULL
        && conf->trailers == NULL)
    {
        return ngx_http_next_header_filter(r);
    }

    switch (r->headers_out.status) {

    case NGX_HTTP_OK:
    case NGX_HTTP_CREATED:
    case NGX_HTTP_NO_CONTENT:
    case NGX_HTTP_PARTIAL_CONTENT:
    case NGX_HTTP_MOVED_PERMANENTLY:
    case NGX_HTTP_MOVED_TEMPORARILY:
    case NGX_HTTP_SEE_OTHER:
    case NGX_HTTP_NOT_MODIFIED:
    case NGX_HTTP_TEMPORARY_REDIRECT:
    case NGX_HTTP_PERMANENT_REDIRECT:
        safe_status = 1;
        break;

    default:
        safe_status = 0;
        break;
    }

    if (conf->expires != NGX_HTTP_EXPIRES_OFF && safe_status) {
        if (ngx_http_set_expires(r, conf) != NGX_OK) {
            return NGX_ERROR;
        }
    }

    if (conf->headers) {
        h = conf->headers->elts;
        for (i = 0; i < conf->headers->nelts; i++) {

            if (!safe_status && !h[i].always) {
                continue;
            }

            if (ngx_http_complex_value(r, &h[i].value, &value) != NGX_OK) {
                return NGX_ERROR;
            }

            if (h[i].handler(r, &h[i], &value) != NGX_OK) {
                return NGX_ERROR;
            }
        }
    }

    if (conf->trailers) {
        h = conf->trailers->elts;
        for (i = 0; i < conf->trailers->nelts; i++) {

            if (!safe_status && !h[i].always) {
                continue;
            }

            r->expect_trailers = 1;
            break;
        }
    }

    return ngx_http_next_header_filter(r);
}
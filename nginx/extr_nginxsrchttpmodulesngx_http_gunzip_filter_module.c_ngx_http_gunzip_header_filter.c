#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_20__ {TYPE_2__* content_encoding; } ;
struct TYPE_21__ {int gzip_vary; int filter_need_in_memory; TYPE_3__ headers_out; int /*<<< orphan*/  pool; scalar_t__ gzip_ok; int /*<<< orphan*/  gzip_tested; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_22__ {TYPE_4__* request; } ;
typedef  TYPE_5__ ngx_http_gunzip_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/  enable; } ;
typedef  TYPE_6__ ngx_http_gunzip_conf_t ;
struct TYPE_18__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {scalar_t__ hash; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_clear_accept_ranges (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_clear_content_length (TYPE_4__*) ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_gunzip_filter_module ; 
 scalar_t__ ngx_http_gzip_ok (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_next_header_filter (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_weak_etag (TYPE_4__*) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_gunzip_header_filter(ngx_http_request_t *r)
{
    ngx_http_gunzip_ctx_t   *ctx;
    ngx_http_gunzip_conf_t  *conf;

    conf = ngx_http_get_module_loc_conf(r, ngx_http_gunzip_filter_module);

    /* TODO support multiple content-codings */
    /* TODO always gunzip - due to configuration or module request */
    /* TODO ignore content encoding? */

    if (!conf->enable
        || r->headers_out.content_encoding == NULL
        || r->headers_out.content_encoding->value.len != 4
        || ngx_strncasecmp(r->headers_out.content_encoding->value.data,
                           (u_char *) "gzip", 4) != 0)
    {
        return ngx_http_next_header_filter(r);
    }

    r->gzip_vary = 1;

    if (!r->gzip_tested) {
        if (ngx_http_gzip_ok(r) == NGX_OK) {
            return ngx_http_next_header_filter(r);
        }

    } else if (r->gzip_ok) {
        return ngx_http_next_header_filter(r);
    }

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_gunzip_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_http_gunzip_filter_module);

    ctx->request = r;

    r->filter_need_in_memory = 1;

    r->headers_out.content_encoding->hash = 0;
    r->headers_out.content_encoding = NULL;

    ngx_http_clear_content_length(r);
    ngx_http_clear_accept_ranges(r);
    ngx_http_weak_etag(r);

    return ngx_http_next_header_filter(r);
}
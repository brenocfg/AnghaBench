#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_10__ {int len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int valid; scalar_t__ len; int /*<<< orphan*/ * data; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
struct TYPE_12__ {TYPE_1__ timefmt; } ;
typedef  TYPE_3__ ngx_http_ssi_ctx_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_SSI_DATE_LEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_TIME_T_LEN ; 
 TYPE_3__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_ssi_filter_module ; 
 TYPE_1__ ngx_http_ssi_timefmt ; 
 int /*<<< orphan*/  ngx_libc_gmtime (int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  ngx_libc_localtime (int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 void* ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_time () ; 
 int /*<<< orphan*/ * strftime (char*,int,char*,struct tm*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_date_gmt_local_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t gmt)
{
    time_t               now;
    ngx_http_ssi_ctx_t  *ctx;
    ngx_str_t           *timefmt;
    struct tm            tm;
    char                 buf[NGX_HTTP_SSI_DATE_LEN];

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;

    now = ngx_time();

    ctx = ngx_http_get_module_ctx(r, ngx_http_ssi_filter_module);

    timefmt = ctx ? &ctx->timefmt : &ngx_http_ssi_timefmt;

    if (timefmt->len == sizeof("%s") - 1
        && timefmt->data[0] == '%' && timefmt->data[1] == 's')
    {
        v->data = ngx_pnalloc(r->pool, NGX_TIME_T_LEN);
        if (v->data == NULL) {
            return NGX_ERROR;
        }

        v->len = ngx_sprintf(v->data, "%T", now) - v->data;

        return NGX_OK;
    }

    if (gmt) {
        ngx_libc_gmtime(now, &tm);
    } else {
        ngx_libc_localtime(now, &tm);
    }

    v->len = strftime(buf, NGX_HTTP_SSI_DATE_LEN,
                      (char *) timefmt->data, &tm);
    if (v->len == 0) {
        return NGX_ERROR;
    }

    v->data = ngx_pnalloc(r->pool, v->len);
    if (v->data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(v->data, buf, v->len);

    return NGX_OK;
}
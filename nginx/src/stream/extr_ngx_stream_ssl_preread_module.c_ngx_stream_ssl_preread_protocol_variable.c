#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int not_found; int valid; int /*<<< orphan*/  data; int /*<<< orphan*/  len; scalar_t__ no_cacheable; } ;
typedef  TYPE_1__ ngx_variable_value_t ;
struct TYPE_9__ {int* version; } ;
typedef  TYPE_2__ ngx_stream_ssl_preread_ctx_t ;
typedef  int /*<<< orphan*/  ngx_stream_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_3__*,char*) ; 
 TYPE_2__* ngx_stream_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_ssl_preread_module ; 

__attribute__((used)) static ngx_int_t
ngx_stream_ssl_preread_protocol_variable(ngx_stream_session_t *s,
    ngx_variable_value_t *v, uintptr_t data)
{
    ngx_str_t                      version;
    ngx_stream_ssl_preread_ctx_t  *ctx;

    ctx = ngx_stream_get_module_ctx(s, ngx_stream_ssl_preread_module);

    if (ctx == NULL) {
        v->not_found = 1;
        return NGX_OK;
    }

    /* SSL_get_version() format */

    ngx_str_null(&version);

    switch (ctx->version[0]) {
    case 0:
        switch (ctx->version[1]) {
        case 2:
            ngx_str_set(&version, "SSLv2");
            break;
        }
        break;
    case 3:
        switch (ctx->version[1]) {
        case 0:
            ngx_str_set(&version, "SSLv3");
            break;
        case 1:
            ngx_str_set(&version, "TLSv1");
            break;
        case 2:
            ngx_str_set(&version, "TLSv1.1");
            break;
        case 3:
            ngx_str_set(&version, "TLSv1.2");
            break;
        case 4:
            ngx_str_set(&version, "TLSv1.3");
            break;
        }
    }

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->len = version.len;
    v->data = version.data;

    return NGX_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int not_found; } ;
typedef  TYPE_1__ ngx_http_variable_value_t ;
struct TYPE_12__ {scalar_t__* uid_got; } ;
typedef  TYPE_2__ ngx_http_userid_ctx_t ;
struct TYPE_13__ {scalar_t__ enable; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_http_userid_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  main; } ;
typedef  TYPE_4__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_USERID_OFF ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_3__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_userid_filter_module ; 
 TYPE_2__* ngx_http_userid_get_uid (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_userid_variable (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_userid_got_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{
    ngx_http_userid_ctx_t   *ctx;
    ngx_http_userid_conf_t  *conf;

    conf = ngx_http_get_module_loc_conf(r->main, ngx_http_userid_filter_module);

    if (conf->enable == NGX_HTTP_USERID_OFF) {
        v->not_found = 1;
        return NGX_OK;
    }

    ctx = ngx_http_userid_get_uid(r->main, conf);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    if (ctx->uid_got[3] != 0) {
        return ngx_http_userid_variable(r->main, v, &conf->name, ctx->uid_got);
    }

    v->not_found = 1;

    return NGX_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
struct TYPE_3__ {int /*<<< orphan*/  get_handler; } ;
typedef  TYPE_1__ ngx_http_variable_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_VAR_CHANGEABLE ; 
 scalar_t__ NGX_OK ; 
 TYPE_1__* ngx_http_add_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_get_variable_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_userid_got ; 
 int /*<<< orphan*/  ngx_http_userid_got_variable ; 
 int /*<<< orphan*/  ngx_http_userid_reset ; 
 scalar_t__ ngx_http_userid_reset_index ; 
 int /*<<< orphan*/  ngx_http_userid_reset_variable ; 
 int /*<<< orphan*/  ngx_http_userid_set ; 
 int /*<<< orphan*/  ngx_http_userid_set_variable ; 

__attribute__((used)) static ngx_int_t
ngx_http_userid_add_variables(ngx_conf_t *cf)
{
    ngx_int_t             n;
    ngx_http_variable_t  *var;

    var = ngx_http_add_variable(cf, &ngx_http_userid_got, 0);
    if (var == NULL) {
        return NGX_ERROR;
    }

    var->get_handler = ngx_http_userid_got_variable;

    var = ngx_http_add_variable(cf, &ngx_http_userid_set, 0);
    if (var == NULL) {
        return NGX_ERROR;
    }

    var->get_handler = ngx_http_userid_set_variable;

    var = ngx_http_add_variable(cf, &ngx_http_userid_reset,
                                NGX_HTTP_VAR_CHANGEABLE);
    if (var == NULL) {
        return NGX_ERROR;
    }

    var->get_handler = ngx_http_userid_reset_variable;

    n = ngx_http_get_variable_index(cf, &ngx_http_userid_reset);
    if (n == NGX_ERROR) {
        return NGX_ERROR;
    }

    ngx_http_userid_reset_index = n;

    return NGX_OK;
}
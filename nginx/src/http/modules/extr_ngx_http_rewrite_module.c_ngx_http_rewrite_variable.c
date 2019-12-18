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
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {scalar_t__ index; int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ ngx_http_script_var_code_t ;
struct TYPE_13__ {int /*<<< orphan*/  codes; } ;
typedef  TYPE_3__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ ngx_http_get_variable_index (TYPE_4__*,TYPE_1__*) ; 
 TYPE_2__* ngx_http_script_start_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_script_var_code ; 

__attribute__((used)) static char *
ngx_http_rewrite_variable(ngx_conf_t *cf, ngx_http_rewrite_loc_conf_t *lcf,
    ngx_str_t *value)
{
    ngx_int_t                    index;
    ngx_http_script_var_code_t  *var_code;

    value->len--;
    value->data++;

    index = ngx_http_get_variable_index(cf, value);

    if (index == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    var_code = ngx_http_script_start_code(cf->pool, &lcf->codes,
                                          sizeof(ngx_http_script_var_code_t));
    if (var_code == NULL) {
        return NGX_CONF_ERROR;
    }

    var_code->code = ngx_http_script_var_code;
    var_code->index = index;

    return NGX_CONF_OK;
}
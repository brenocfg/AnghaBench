#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  get_handler; int /*<<< orphan*/  flags; TYPE_4__ name; } ;
typedef  TYPE_1__ ngx_http_variable_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_1__* ngx_http_add_variable (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_http_geoip_vars ; 

__attribute__((used)) static ngx_int_t
ngx_http_geoip_add_variables(ngx_conf_t *cf)
{
    ngx_http_variable_t  *var, *v;

    for (v = ngx_http_geoip_vars; v->name.len; v++) {
        var = ngx_http_add_variable(cf, &v->name, v->flags);
        if (var == NULL) {
            return NGX_ERROR;
        }

        var->get_handler = v->get_handler;
        var->data = v->data;
    }

    return NGX_OK;
}
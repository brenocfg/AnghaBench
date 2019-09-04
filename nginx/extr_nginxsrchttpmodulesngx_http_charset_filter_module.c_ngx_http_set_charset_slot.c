#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  charsets; } ;
typedef  TYPE_3__ ngx_http_charset_main_conf_t ;
struct TYPE_16__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_17__ {int offset; } ;
typedef  TYPE_5__ ngx_command_t ;
struct TYPE_13__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_CHARSET_OFF ; 
 scalar_t__ NGX_HTTP_CHARSET_VAR ; 
 int /*<<< orphan*/  charset ; 
 scalar_t__ ngx_http_add_charset (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_charset_filter_module ; 
 int /*<<< orphan*/  ngx_http_charset_loc_conf_t ; 
 TYPE_3__* ngx_http_conf_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_get_variable_index (TYPE_4__*,TYPE_2__*) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_set_charset_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    ngx_int_t                     *cp;
    ngx_str_t                     *value, var;
    ngx_http_charset_main_conf_t  *mcf;

    cp = (ngx_int_t *) (p + cmd->offset);

    if (*cp != NGX_CONF_UNSET) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (cmd->offset == offsetof(ngx_http_charset_loc_conf_t, charset)
        && ngx_strcmp(value[1].data, "off") == 0)
    {
        *cp = NGX_HTTP_CHARSET_OFF;
        return NGX_CONF_OK;
    }


    if (value[1].data[0] == '$') {
        var.len = value[1].len - 1;
        var.data = value[1].data + 1;

        *cp = ngx_http_get_variable_index(cf, &var);

        if (*cp == NGX_ERROR) {
            return NGX_CONF_ERROR;
        }

        *cp += NGX_HTTP_CHARSET_VAR;

        return NGX_CONF_OK;
    }

    mcf = ngx_http_conf_get_module_main_conf(cf,
                                             ngx_http_charset_filter_module);

    *cp = ngx_http_add_charset(&mcf->charsets, &value[1]);
    if (*cp == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}
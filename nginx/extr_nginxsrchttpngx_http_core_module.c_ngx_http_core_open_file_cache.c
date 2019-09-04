#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_9__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/ * open_file_cache; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_8__ {size_t nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atoi (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ngx_open_file_cache_init (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int ngx_parse_time (TYPE_2__*,int) ; 
 scalar_t__ ngx_strcmp (scalar_t__,char*) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_core_open_file_cache(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    time_t       inactive;
    ngx_str_t   *value, s;
    ngx_int_t    max;
    ngx_uint_t   i;

    if (clcf->open_file_cache != NGX_CONF_UNSET_PTR) {
        return "is duplicate";
    }

    value = cf->args->elts;

    max = 0;
    inactive = 60;

    for (i = 1; i < cf->args->nelts; i++) {

        if (ngx_strncmp(value[i].data, "max=", 4) == 0) {

            max = ngx_atoi(value[i].data + 4, value[i].len - 4);
            if (max <= 0) {
                goto failed;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "inactive=", 9) == 0) {

            s.len = value[i].len - 9;
            s.data = value[i].data + 9;

            inactive = ngx_parse_time(&s, 1);
            if (inactive == (time_t) NGX_ERROR) {
                goto failed;
            }

            continue;
        }

        if (ngx_strcmp(value[i].data, "off") == 0) {

            clcf->open_file_cache = NULL;

            continue;
        }

    failed:

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid \"open_file_cache\" parameter \"%V\"",
                           &value[i]);
        return NGX_CONF_ERROR;
    }

    if (clcf->open_file_cache == NULL) {
        return NGX_CONF_OK;
    }

    if (max == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                        "\"open_file_cache\" must have the \"max\" parameter");
        return NGX_CONF_ERROR;
    }

    clcf->open_file_cache = ngx_open_file_cache_init(cf->pool, max, inactive);
    if (clcf->open_file_cache) {
        return NGX_CONF_OK;
    }

    return NGX_CONF_ERROR;
}
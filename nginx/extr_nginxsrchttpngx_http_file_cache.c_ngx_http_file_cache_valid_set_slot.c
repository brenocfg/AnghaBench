#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int ngx_uint_t ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_14__ {int status; scalar_t__ valid; } ;
typedef  TYPE_3__ ngx_http_cache_valid_t ;
struct TYPE_15__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_16__ {int offset; } ;
typedef  TYPE_5__ ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_12__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 scalar_t__ ngx_parse_time (TYPE_2__*,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

char *
ngx_http_file_cache_valid_set_slot(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    char  *p = conf;

    time_t                    valid;
    ngx_str_t                *value;
    ngx_int_t                 status;
    ngx_uint_t                i, n;
    ngx_array_t             **a;
    ngx_http_cache_valid_t   *v;
    static ngx_uint_t         statuses[] = { 200, 301, 302 };

    a = (ngx_array_t **) (p + cmd->offset);

    if (*a == NGX_CONF_UNSET_PTR) {
        *a = ngx_array_create(cf->pool, 1, sizeof(ngx_http_cache_valid_t));
        if (*a == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    value = cf->args->elts;
    n = cf->args->nelts - 1;

    valid = ngx_parse_time(&value[n], 1);
    if (valid == (time_t) NGX_ERROR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid time value \"%V\"", &value[n]);
        return NGX_CONF_ERROR;
    }

    if (n == 1) {

        for (i = 0; i < 3; i++) {
            v = ngx_array_push(*a);
            if (v == NULL) {
                return NGX_CONF_ERROR;
            }

            v->status = statuses[i];
            v->valid = valid;
        }

        return NGX_CONF_OK;
    }

    for (i = 1; i < n; i++) {

        if (ngx_strcmp(value[i].data, "any") == 0) {

            status = 0;

        } else {

            status = ngx_atoi(value[i].data, value[i].len);
            if (status < 100 || status > 599) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid status \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }
        }

        v = ngx_array_push(*a);
        if (v == NULL) {
            return NGX_CONF_ERROR;
        }

        v->status = status;
        v->valid = valid;
    }

    return NGX_CONF_OK;
}
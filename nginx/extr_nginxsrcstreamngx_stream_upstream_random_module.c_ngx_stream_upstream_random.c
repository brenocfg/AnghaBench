#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ init_upstream; } ;
struct TYPE_13__ {int flags; TYPE_1__ peer; } ;
typedef  TYPE_3__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_14__ {int two; } ;
typedef  TYPE_4__ ngx_stream_upstream_random_srv_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_16__ {TYPE_2__* args; } ;
typedef  TYPE_6__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_12__ {int nelts; TYPE_5__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int NGX_STREAM_UPSTREAM_CREATE ; 
 int NGX_STREAM_UPSTREAM_DOWN ; 
 int NGX_STREAM_UPSTREAM_FAIL_TIMEOUT ; 
 int NGX_STREAM_UPSTREAM_MAX_CONNS ; 
 int NGX_STREAM_UPSTREAM_MAX_FAILS ; 
 int NGX_STREAM_UPSTREAM_WEIGHT ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* ngx_stream_conf_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_stream_upstream_init_random ; 
 int /*<<< orphan*/  ngx_stream_upstream_module ; 

__attribute__((used)) static char *
ngx_stream_upstream_random(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_upstream_random_srv_conf_t  *rcf = conf;

    ngx_str_t                       *value;
    ngx_stream_upstream_srv_conf_t  *uscf;

    uscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_upstream_module);

    if (uscf->peer.init_upstream) {
        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                           "load balancing method redefined");
    }

    uscf->peer.init_upstream = ngx_stream_upstream_init_random;

    uscf->flags = NGX_STREAM_UPSTREAM_CREATE
                  |NGX_STREAM_UPSTREAM_WEIGHT
                  |NGX_STREAM_UPSTREAM_MAX_CONNS
                  |NGX_STREAM_UPSTREAM_MAX_FAILS
                  |NGX_STREAM_UPSTREAM_FAIL_TIMEOUT
                  |NGX_STREAM_UPSTREAM_DOWN;

    if (cf->args->nelts == 1) {
        return NGX_CONF_OK;
    }

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "two") == 0) {
        rcf->two = 1;

    } else {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[1]);
        return NGX_CONF_ERROR;
    }

    if (cf->args->nelts == 2) {
        return NGX_CONF_OK;
    }

    if (ngx_strcmp(value[2].data, "least_conn") != 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid parameter \"%V\"", &value[2]);
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}
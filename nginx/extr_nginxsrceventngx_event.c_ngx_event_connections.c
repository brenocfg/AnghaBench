#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_12__ {scalar_t__ connections; } ;
typedef  TYPE_4__ ngx_event_conf_t ;
struct TYPE_13__ {TYPE_1__* cycle; TYPE_2__* args; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_10__ {TYPE_3__* elts; } ;
struct TYPE_9__ {scalar_t__ connection_n; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,TYPE_3__*) ; 

__attribute__((used)) static char *
ngx_event_connections(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_event_conf_t  *ecf = conf;

    ngx_str_t  *value;

    if (ecf->connections != NGX_CONF_UNSET_UINT) {
        return "is duplicate";
    }

    value = cf->args->elts;
    ecf->connections = ngx_atoi(value[1].data, value[1].len);
    if (ecf->connections == (ngx_uint_t) NGX_ERROR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid number \"%V\"", &value[1]);

        return NGX_CONF_ERROR;
    }

    cf->cycle->connection_n = ecf->connections;

    return NGX_CONF_OK;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_11__ {size_t sbrk_size; } ;
typedef  TYPE_3__ ngx_http_degradation_main_conf_t ;
struct TYPE_12__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_9__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 size_t ngx_parse_size (TYPE_2__*) ; 
 scalar_t__ ngx_strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static char *
ngx_http_degradation(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_degradation_main_conf_t  *dmcf = conf;

    ngx_str_t  *value, s;

    value = cf->args->elts;

    if (ngx_strncmp(value[1].data, "sbrk=", 5) == 0) {

        s.len = value[1].len - 5;
        s.data = value[1].data + 5;

        dmcf->sbrk_size = ngx_parse_size(&s);
        if (dmcf->sbrk_size == (size_t) NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid sbrk size \"%V\"", &value[1]);
            return NGX_CONF_ERROR;
        }

        return NGX_CONF_OK;
    }

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "invalid parameter \"%V\"", &value[1]);

    return NGX_CONF_ERROR;
}
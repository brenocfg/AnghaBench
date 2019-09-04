#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_7__ {char* data; scalar_t__ len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {int /*<<< orphan*/  priority; } ;
typedef  TYPE_3__ ngx_core_conf_t ;
struct TYPE_9__ {TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_6__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  ngx_atoi (char*,scalar_t__) ; 

__attribute__((used)) static char *
ngx_set_priority(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_core_conf_t  *ccf = conf;

    ngx_str_t        *value;
    ngx_uint_t        n, minus;

    if (ccf->priority != 0) {
        return "is duplicate";
    }

    value = cf->args->elts;

    if (value[1].data[0] == '-') {
        n = 1;
        minus = 1;

    } else if (value[1].data[0] == '+') {
        n = 1;
        minus = 0;

    } else {
        n = 0;
        minus = 0;
    }

    ccf->priority = ngx_atoi(&value[1].data[n], value[1].len - n);
    if (ccf->priority == NGX_ERROR) {
        return "invalid number";
    }

    if (minus) {
        ccf->priority = -ccf->priority;
    }

    return NGX_CONF_OK;
}
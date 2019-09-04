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
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_10__ {int /*<<< orphan*/ * complex_value; int /*<<< orphan*/ * value; TYPE_3__* cf; } ;
typedef  TYPE_2__ ngx_http_compile_complex_value_t ;
struct TYPE_11__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;
struct TYPE_12__ {int offset; } ;
typedef  TYPE_4__ ngx_command_t ;
struct TYPE_9__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_compile_complex_value (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,int) ; 

char *
ngx_http_set_complex_value_slot(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    ngx_str_t                          *value;
    ngx_http_complex_value_t          **cv;
    ngx_http_compile_complex_value_t    ccv;

    cv = (ngx_http_complex_value_t **) (p + cmd->offset);

    if (*cv != NULL) {
        return "is duplicate";
    }

    *cv = ngx_palloc(cf->pool, sizeof(ngx_http_complex_value_t));
    if (*cv == NULL) {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    ngx_memzero(&ccv, sizeof(ngx_http_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = *cv;

    if (ngx_http_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}
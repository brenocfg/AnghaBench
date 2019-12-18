#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_15__ {TYPE_2__ value; } ;
struct TYPE_16__ {TYPE_3__ text; } ;
typedef  TYPE_4__ ngx_stream_return_srv_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  handler; } ;
typedef  TYPE_5__ ngx_stream_core_srv_conf_t ;
struct TYPE_18__ {TYPE_3__* complex_value; int /*<<< orphan*/ * value; TYPE_7__* cf; } ;
typedef  TYPE_6__ ngx_stream_compile_complex_value_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_19__ {TYPE_1__* args; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_13__ {int /*<<< orphan*/ * elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 scalar_t__ ngx_stream_compile_complex_value (TYPE_6__*) ; 
 TYPE_5__* ngx_stream_conf_get_module_srv_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 int /*<<< orphan*/  ngx_stream_return_handler ; 

__attribute__((used)) static char *
ngx_stream_return(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_return_srv_conf_t *rscf = conf;

    ngx_str_t                           *value;
    ngx_stream_core_srv_conf_t          *cscf;
    ngx_stream_compile_complex_value_t   ccv;

    if (rscf->text.value.data) {
        return "is duplicate";
    }

    value = cf->args->elts;

    ngx_memzero(&ccv, sizeof(ngx_stream_compile_complex_value_t));

    ccv.cf = cf;
    ccv.value = &value[1];
    ccv.complex_value = &rscf->text;

    if (ngx_stream_compile_complex_value(&ccv) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    cscf = ngx_stream_conf_get_module_srv_conf(cf, ngx_stream_core_module);

    cscf->handler = ngx_stream_return_handler;

    return NGX_CONF_OK;
}
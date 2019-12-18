#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_19__ {TYPE_5__* (* create_app_conf ) (TYPE_8__*) ;} ;
typedef  TYPE_3__ ngx_rtmp_module_t ;
struct TYPE_20__ {int /*<<< orphan*/  applications; } ;
typedef  TYPE_4__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_21__ {int /*<<< orphan*/  name; struct TYPE_21__** app_conf; } ;
typedef  TYPE_5__ ngx_rtmp_core_app_conf_t ;
struct TYPE_22__ {TYPE_4__** srv_conf; TYPE_5__** app_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_6__ ngx_rtmp_conf_ctx_t ;
struct TYPE_23__ {scalar_t__ type; size_t ctx_index; TYPE_3__* ctx; } ;
typedef  TYPE_7__ ngx_module_t ;
typedef  size_t ngx_int_t ;
struct TYPE_24__ {int /*<<< orphan*/  cmd_type; TYPE_6__* ctx; TYPE_2__* args; TYPE_1__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_18__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_17__ {TYPE_7__** modules; } ;
struct TYPE_16__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int /*<<< orphan*/  NGX_RTMP_APP_CONF ; 
 scalar_t__ NGX_RTMP_MODULE ; 
 TYPE_5__** ngx_array_push (int /*<<< orphan*/ *) ; 
 char* ngx_conf_parse (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_7__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_11__ ngx_rtmp_core_module ; 
 int ngx_rtmp_max_module ; 
 TYPE_5__* stub1 (TYPE_8__*) ; 

__attribute__((used)) static char *
ngx_rtmp_core_application(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                       *rv;
    ngx_int_t                   i;
    ngx_str_t                  *value;
    ngx_conf_t                  save;
    ngx_module_t              **modules;
    ngx_rtmp_module_t          *module;
    ngx_rtmp_conf_ctx_t        *ctx, *pctx;
    ngx_rtmp_core_srv_conf_t   *cscf;
    ngx_rtmp_core_app_conf_t   *cacf, **cacfp;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_rtmp_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    pctx = cf->ctx;
    ctx->main_conf = pctx->main_conf;
    ctx->srv_conf = pctx->srv_conf;

    ctx->app_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->app_conf == NULL) {
        return NGX_CONF_ERROR;
    }

#if (nginx_version >= 1009011)
    modules = cf->cycle->modules;
#else
    modules = ngx_modules;
#endif

    for (i = 0; modules[i]; i++) {
        if (modules[i]->type != NGX_RTMP_MODULE) {
            continue;
        }

        module = modules[i]->ctx;

        if (module->create_app_conf) {
            ctx->app_conf[modules[i]->ctx_index] = module->create_app_conf(cf);
            if (ctx->app_conf[modules[i]->ctx_index] == NULL) {
                return NGX_CONF_ERROR;
            }
        }
    }

    cacf = ctx->app_conf[ngx_rtmp_core_module.ctx_index];
    cacf->app_conf = ctx->app_conf;

    value = cf->args->elts;

    cacf->name = value[1];
    cscf = pctx->srv_conf[ngx_rtmp_core_module.ctx_index];

    cacfp = ngx_array_push(&cscf->applications);
    if (cacfp == NULL) {
        return NGX_CONF_ERROR;
    }

    *cacfp = cacf;

    save = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_RTMP_APP_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf= save;

    return rv;
}
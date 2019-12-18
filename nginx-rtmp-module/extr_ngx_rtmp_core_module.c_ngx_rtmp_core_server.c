#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_17__ {void* (* create_app_conf ) (TYPE_7__*) ;void* (* create_srv_conf ) (TYPE_7__*) ;} ;
typedef  TYPE_2__ ngx_rtmp_module_t ;
struct TYPE_18__ {TYPE_5__* ctx; } ;
typedef  TYPE_3__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_19__ {int /*<<< orphan*/  servers; } ;
typedef  TYPE_4__ ngx_rtmp_core_main_conf_t ;
struct TYPE_20__ {TYPE_4__** main_conf; TYPE_3__** srv_conf; void** app_conf; } ;
typedef  TYPE_5__ ngx_rtmp_conf_ctx_t ;
struct TYPE_21__ {scalar_t__ type; size_t ctx_index; TYPE_2__* ctx; } ;
typedef  TYPE_6__ ngx_module_t ;
struct TYPE_22__ {int /*<<< orphan*/  cmd_type; TYPE_5__* ctx; TYPE_1__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_16__ {TYPE_6__** modules; } ;
struct TYPE_15__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 scalar_t__ NGX_RTMP_MODULE ; 
 int /*<<< orphan*/  NGX_RTMP_SRV_CONF ; 
 TYPE_3__** ngx_array_push (int /*<<< orphan*/ *) ; 
 char* ngx_conf_parse (TYPE_7__*,int /*<<< orphan*/ *) ; 
 TYPE_6__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_11__ ngx_rtmp_core_module ; 
 int ngx_rtmp_max_module ; 
 void* stub1 (TYPE_7__*) ; 
 void* stub2 (TYPE_7__*) ; 

__attribute__((used)) static char *
ngx_rtmp_core_server(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                       *rv;
    void                       *mconf;
    ngx_uint_t                  m;
    ngx_conf_t                  pcf;
    ngx_module_t              **modules;
    ngx_rtmp_module_t          *module;
    ngx_rtmp_conf_ctx_t        *ctx, *rtmp_ctx;
    ngx_rtmp_core_srv_conf_t   *cscf, **cscfp;
    ngx_rtmp_core_main_conf_t  *cmcf;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_rtmp_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    rtmp_ctx = cf->ctx;
    ctx->main_conf = rtmp_ctx->main_conf;

    /* the server{}'s srv_conf */

    ctx->srv_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx->app_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->app_conf == NULL) {
        return NGX_CONF_ERROR;
    }

#if (nginx_version >= 1009011)
    modules = cf->cycle->modules;
#else
    modules = ngx_modules;
#endif

    for (m = 0; modules[m]; m++) {
        if (modules[m]->type != NGX_RTMP_MODULE) {
            continue;
        }

        module = modules[m]->ctx;

        if (module->create_srv_conf) {
            mconf = module->create_srv_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->srv_conf[modules[m]->ctx_index] = mconf;
        }

        if (module->create_app_conf) {
            mconf = module->create_app_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->app_conf[modules[m]->ctx_index] = mconf;
        }
    }

    /* the server configuration context */

    cscf = ctx->srv_conf[ngx_rtmp_core_module.ctx_index];
    cscf->ctx = ctx;

    cmcf = ctx->main_conf[ngx_rtmp_core_module.ctx_index];

    cscfp = ngx_array_push(&cmcf->servers);
    if (cscfp == NULL) {
        return NGX_CONF_ERROR;
    }

    *cscfp = cscf;


    /* parse inside server{} */

    pcf = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_RTMP_SRV_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pcf;

    return rv;
}
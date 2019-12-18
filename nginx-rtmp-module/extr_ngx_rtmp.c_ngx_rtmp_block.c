#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_33__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_29__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_39__ {scalar_t__ (* preconfiguration ) (TYPE_8__*) ;char* (* init_main_conf ) (TYPE_8__*,TYPE_5__*) ;char* (* merge_srv_conf ) (TYPE_8__*,TYPE_4__*,TYPE_4__*) ;char* (* merge_app_conf ) (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* postconfiguration ) (TYPE_8__*) ;int /*<<< orphan*/ * (* create_app_conf ) (TYPE_8__*) ;TYPE_4__* (* create_srv_conf ) (TYPE_8__*) ;TYPE_5__* (* create_main_conf ) (TYPE_8__*) ;} ;
typedef  TYPE_3__ ngx_rtmp_module_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_listen_t ;
struct TYPE_40__ {TYPE_6__* ctx; int /*<<< orphan*/  applications; } ;
typedef  TYPE_4__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_37__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_35__ {size_t nelts; TYPE_4__** elts; } ;
struct TYPE_41__ {TYPE_2__ listen; TYPE_1__ servers; } ;
typedef  TYPE_5__ ngx_rtmp_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_conf_port_t ;
struct TYPE_42__ {int /*<<< orphan*/ ** app_conf; TYPE_4__** srv_conf; TYPE_5__** main_conf; } ;
typedef  TYPE_6__ ngx_rtmp_conf_ctx_t ;
struct TYPE_43__ {scalar_t__ type; size_t ctx_index; TYPE_3__* ctx; } ;
typedef  TYPE_7__ ngx_module_t ;
struct TYPE_44__ {int /*<<< orphan*/  temp_pool; TYPE_6__* ctx; int /*<<< orphan*/  cmd_type; scalar_t__ module_type; TYPE_33__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
struct TYPE_38__ {TYPE_7__** modules; } ;
struct TYPE_36__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_MAIN_CONF ; 
 scalar_t__ NGX_RTMP_MODULE ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 char* ngx_conf_parse (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int ngx_count_modules (TYPE_33__*,scalar_t__) ; 
 TYPE_7__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_rtmp_add_ports (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_29__ ngx_rtmp_core_module ; 
 scalar_t__ ngx_rtmp_init_event_handlers (TYPE_8__*,TYPE_5__*) ; 
 scalar_t__ ngx_rtmp_init_events (TYPE_8__*,TYPE_5__*) ; 
 int ngx_rtmp_max_module ; 
 char* ngx_rtmp_merge_applications (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_3__*,size_t) ; 
 char* ngx_rtmp_optimize_servers (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* stub1 (TYPE_8__*) ; 
 TYPE_4__* stub2 (TYPE_8__*) ; 
 int /*<<< orphan*/ * stub3 (TYPE_8__*) ; 
 scalar_t__ stub4 (TYPE_8__*) ; 
 char* stub5 (TYPE_8__*,TYPE_5__*) ; 
 char* stub6 (TYPE_8__*,TYPE_4__*,TYPE_4__*) ; 
 char* stub7 (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub8 (TYPE_8__*) ; 

__attribute__((used)) static char *
ngx_rtmp_block(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                        *rv;
    ngx_uint_t                   i, m, mi, s;
    ngx_conf_t                   pcf;
    ngx_array_t                  ports;
    ngx_module_t               **modules;
    ngx_rtmp_listen_t           *listen;
    ngx_rtmp_module_t           *module;
    ngx_rtmp_conf_ctx_t         *ctx;
    ngx_rtmp_core_srv_conf_t    *cscf, **cscfp;
    ngx_rtmp_core_main_conf_t   *cmcf;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_rtmp_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    *(ngx_rtmp_conf_ctx_t **) conf = ctx;

    /* count the number of the rtmp modules and set up their indices */

#if (nginx_version >= 1009011)

    ngx_rtmp_max_module = ngx_count_modules(cf->cycle, NGX_RTMP_MODULE);

#else

    ngx_rtmp_max_module = 0;
    for (m = 0; ngx_modules[m]; m++) {
        if (ngx_modules[m]->type != NGX_RTMP_MODULE) {
            continue;
        }

        ngx_modules[m]->ctx_index = ngx_rtmp_max_module++;
    }

#endif


    /* the rtmp main_conf context, it is the same in the all rtmp contexts */

    ctx->main_conf = ngx_pcalloc(cf->pool,
                                 sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->main_conf == NULL) {
        return NGX_CONF_ERROR;
    }


    /*
     * the rtmp null srv_conf context, it is used to merge
     * the server{}s' srv_conf's
     */

    ctx->srv_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_CONF_ERROR;
    }


    /*
     * the rtmp null app_conf context, it is used to merge
     * the server{}s' app_conf's
     */

    ctx->app_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_rtmp_max_module);
    if (ctx->app_conf == NULL) {
        return NGX_CONF_ERROR;
    }


    /*
     * create the main_conf's, the null srv_conf's, and the null app_conf's
     * of the all rtmp modules
     */

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
        mi = modules[m]->ctx_index;

        if (module->create_main_conf) {
            ctx->main_conf[mi] = module->create_main_conf(cf);
            if (ctx->main_conf[mi] == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        if (module->create_srv_conf) {
            ctx->srv_conf[mi] = module->create_srv_conf(cf);
            if (ctx->srv_conf[mi] == NULL) {
                return NGX_CONF_ERROR;
            }
        }

        if (module->create_app_conf) {
            ctx->app_conf[mi] = module->create_app_conf(cf);
            if (ctx->app_conf[mi] == NULL) {
                return NGX_CONF_ERROR;
            }
        }
    }

    pcf = *cf;
    cf->ctx = ctx;

    for (m = 0; modules[m]; m++) {
        if (modules[m]->type != NGX_RTMP_MODULE) {
            continue;
        }

        module = modules[m]->ctx;

        if (module->preconfiguration) {
            if (module->preconfiguration(cf) != NGX_OK) {
                return NGX_CONF_ERROR;
            }
        }
    }

    /* parse inside the rtmp{} block */

    cf->module_type = NGX_RTMP_MODULE;
    cf->cmd_type = NGX_RTMP_MAIN_CONF;
    rv = ngx_conf_parse(cf, NULL);

    if (rv != NGX_CONF_OK) {
        *cf = pcf;
        return rv;
    }


    /* init rtmp{} main_conf's, merge the server{}s' srv_conf's */

    cmcf = ctx->main_conf[ngx_rtmp_core_module.ctx_index];
    cscfp = cmcf->servers.elts;

    for (m = 0; modules[m]; m++) {
        if (modules[m]->type != NGX_RTMP_MODULE) {
            continue;
        }

        module = modules[m]->ctx;
        mi = modules[m]->ctx_index;

        /* init rtmp{} main_conf's */

        cf->ctx = ctx;

        if (module->init_main_conf) {
            rv = module->init_main_conf(cf, ctx->main_conf[mi]);
            if (rv != NGX_CONF_OK) {
                *cf = pcf;
                return rv;
            }
        }

        for (s = 0; s < cmcf->servers.nelts; s++) {

            /* merge the server{}s' srv_conf's */

            cf->ctx = cscfp[s]->ctx;

            if (module->merge_srv_conf) {
                rv = module->merge_srv_conf(cf,
                                            ctx->srv_conf[mi],
                                            cscfp[s]->ctx->srv_conf[mi]);
                if (rv != NGX_CONF_OK) {
                    *cf = pcf;
                    return rv;
                }
            }

            if (module->merge_app_conf) {

                /* merge the server{}'s app_conf */

                /*ctx->app_conf = cscfp[s]->ctx->loc_conf;*/

                rv = module->merge_app_conf(cf,
                                            ctx->app_conf[mi],
                                            cscfp[s]->ctx->app_conf[mi]);
                if (rv != NGX_CONF_OK) {
                    *cf = pcf;
                    return rv;
                }

                /* merge the applications{}' app_conf's */

                cscf = cscfp[s]->ctx->srv_conf[ngx_rtmp_core_module.ctx_index];

                rv = ngx_rtmp_merge_applications(cf, &cscf->applications,
                                            cscfp[s]->ctx->app_conf,
                                            module, mi);
                if (rv != NGX_CONF_OK) {
                    *cf = pcf;
                    return rv;
                }
            }

        }
    }


    if (ngx_rtmp_init_events(cf, cmcf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    for (m = 0; modules[m]; m++) {
        if (modules[m]->type != NGX_RTMP_MODULE) {
            continue;
        }

        module = modules[m]->ctx;

        if (module->postconfiguration) {
            if (module->postconfiguration(cf) != NGX_OK) {
                return NGX_CONF_ERROR;
            }
        }
    }

    *cf = pcf;

    if (ngx_rtmp_init_event_handlers(cf, cmcf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ngx_array_init(&ports, cf->temp_pool, 4, sizeof(ngx_rtmp_conf_port_t))
        != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    listen = cmcf->listen.elts;

    for (i = 0; i < cmcf->listen.nelts; i++) {
        if (ngx_rtmp_add_ports(cf, &ports, &listen[i]) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    return ngx_rtmp_optimize_servers(cf, &ports);
}
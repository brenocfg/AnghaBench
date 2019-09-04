#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {void* (* create_srv_conf ) (TYPE_7__*) ;} ;
typedef  TYPE_3__ ngx_mail_module_t ;
struct TYPE_17__ {int /*<<< orphan*/  line; int /*<<< orphan*/  file_name; int /*<<< orphan*/  listen; TYPE_6__* ctx; } ;
typedef  TYPE_4__ ngx_mail_core_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  servers; } ;
typedef  TYPE_5__ ngx_mail_core_main_conf_t ;
struct TYPE_19__ {TYPE_5__** main_conf; TYPE_4__** srv_conf; } ;
typedef  TYPE_6__ ngx_mail_conf_ctx_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; int /*<<< orphan*/  cmd_type; TYPE_6__* ctx; TYPE_2__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_15__ {TYPE_1__** modules; } ;
struct TYPE_14__ {scalar_t__ type; size_t ctx_index; TYPE_3__* ctx; } ;
struct TYPE_13__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_MAIL_MODULE ; 
 int /*<<< orphan*/  NGX_MAIL_SRV_CONF ; 
 TYPE_4__** ngx_array_push (int /*<<< orphan*/ *) ; 
 char* ngx_conf_parse (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__ ngx_mail_core_module ; 
 int ngx_mail_max_module ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* stub1 (TYPE_7__*) ; 

__attribute__((used)) static char *
ngx_mail_core_server(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                       *rv;
    void                       *mconf;
    ngx_uint_t                  m;
    ngx_conf_t                  pcf;
    ngx_mail_module_t          *module;
    ngx_mail_conf_ctx_t        *ctx, *mail_ctx;
    ngx_mail_core_srv_conf_t   *cscf, **cscfp;
    ngx_mail_core_main_conf_t  *cmcf;

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_mail_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    mail_ctx = cf->ctx;
    ctx->main_conf = mail_ctx->main_conf;

    /* the server{}'s srv_conf */

    ctx->srv_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_mail_max_module);
    if (ctx->srv_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    for (m = 0; cf->cycle->modules[m]; m++) {
        if (cf->cycle->modules[m]->type != NGX_MAIL_MODULE) {
            continue;
        }

        module = cf->cycle->modules[m]->ctx;

        if (module->create_srv_conf) {
            mconf = module->create_srv_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->srv_conf[cf->cycle->modules[m]->ctx_index] = mconf;
        }
    }

    /* the server configuration context */

    cscf = ctx->srv_conf[ngx_mail_core_module.ctx_index];
    cscf->ctx = ctx;

    cmcf = ctx->main_conf[ngx_mail_core_module.ctx_index];

    cscfp = ngx_array_push(&cmcf->servers);
    if (cscfp == NULL) {
        return NGX_CONF_ERROR;
    }

    *cscfp = cscf;


    /* parse inside server{} */

    pcf = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_MAIL_SRV_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pcf;

    if (rv == NGX_CONF_OK && !cscf->listen) {
        ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                      "no \"listen\" is defined for server in %s:%ui",
                      cscf->file_name, cscf->line);
        return NGX_CONF_ERROR;
    }

    return rv;
}
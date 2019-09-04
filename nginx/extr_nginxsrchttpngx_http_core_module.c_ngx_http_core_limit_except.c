#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_24__ {void* (* create_loc_conf ) (TYPE_9__*) ;} ;
typedef  TYPE_5__ ngx_http_module_t ;
struct TYPE_25__ {int method; scalar_t__ name; } ;
typedef  TYPE_6__ ngx_http_method_name_t ;
struct TYPE_26__ {int limit_except; int noname; int lmt_excpt; int /*<<< orphan*/  locations; int /*<<< orphan*/  name; struct TYPE_26__** loc_conf; struct TYPE_26__** limit_except_loc_conf; } ;
typedef  TYPE_7__ ngx_http_core_loc_conf_t ;
struct TYPE_27__ {TYPE_7__** loc_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_8__ ngx_http_conf_ctx_t ;
struct TYPE_28__ {int /*<<< orphan*/  cmd_type; TYPE_8__* ctx; TYPE_3__* cycle; int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_9__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_22__ {TYPE_2__** modules; } ;
struct TYPE_21__ {scalar_t__ type; size_t ctx_index; TYPE_5__* ctx; } ;
struct TYPE_20__ {size_t nelts; TYPE_4__* elts; } ;
struct TYPE_19__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int NGX_HTTP_GET ; 
 scalar_t__ NGX_HTTP_HEAD ; 
 int /*<<< orphan*/  NGX_HTTP_LMT_CONF ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 char* ngx_conf_parse (TYPE_9__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_add_location (TYPE_9__*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_12__ ngx_http_core_module ; 
 int ngx_http_max_module ; 
 TYPE_6__* ngx_methods_names ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcasecmp (int /*<<< orphan*/ ,scalar_t__) ; 
 void* stub1 (TYPE_9__*) ; 

__attribute__((used)) static char *
ngx_http_core_limit_except(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *pclcf = conf;

    char                      *rv;
    void                      *mconf;
    ngx_str_t                 *value;
    ngx_uint_t                 i;
    ngx_conf_t                 save;
    ngx_http_module_t         *module;
    ngx_http_conf_ctx_t       *ctx, *pctx;
    ngx_http_method_name_t    *name;
    ngx_http_core_loc_conf_t  *clcf;

    if (pclcf->limit_except) {
        return "is duplicate";
    }

    pclcf->limit_except = 0xffffffff;

    value = cf->args->elts;

    for (i = 1; i < cf->args->nelts; i++) {
        for (name = ngx_methods_names; name->name; name++) {

            if (ngx_strcasecmp(value[i].data, name->name) == 0) {
                pclcf->limit_except &= name->method;
                goto next;
            }
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid method \"%V\"", &value[i]);
        return NGX_CONF_ERROR;

    next:
        continue;
    }

    if (!(pclcf->limit_except & NGX_HTTP_GET)) {
        pclcf->limit_except &= (uint32_t) ~NGX_HTTP_HEAD;
    }

    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_http_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    pctx = cf->ctx;
    ctx->main_conf = pctx->main_conf;
    ctx->srv_conf = pctx->srv_conf;

    ctx->loc_conf = ngx_pcalloc(cf->pool, sizeof(void *) * ngx_http_max_module);
    if (ctx->loc_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    for (i = 0; cf->cycle->modules[i]; i++) {
        if (cf->cycle->modules[i]->type != NGX_HTTP_MODULE) {
            continue;
        }

        module = cf->cycle->modules[i]->ctx;

        if (module->create_loc_conf) {

            mconf = module->create_loc_conf(cf);
            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            ctx->loc_conf[cf->cycle->modules[i]->ctx_index] = mconf;
        }
    }


    clcf = ctx->loc_conf[ngx_http_core_module.ctx_index];
    pclcf->limit_except_loc_conf = ctx->loc_conf;
    clcf->loc_conf = ctx->loc_conf;
    clcf->name = pclcf->name;
    clcf->noname = 1;
    clcf->lmt_excpt = 1;

    if (ngx_http_add_location(cf, &pclcf->locations, clcf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    save = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_HTTP_LMT_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    return rv;
}
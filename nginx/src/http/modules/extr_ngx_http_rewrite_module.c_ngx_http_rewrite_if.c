#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_25__ {int next; TYPE_4__** loc_conf; int /*<<< orphan*/  code; } ;
typedef  TYPE_3__ ngx_http_script_if_code_t ;
struct TYPE_26__ {int noname; TYPE_19__* codes; int /*<<< orphan*/  locations; int /*<<< orphan*/  name; struct TYPE_26__** loc_conf; } ;
typedef  TYPE_4__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_27__ {void* (* create_loc_conf ) (TYPE_8__*) ;} ;
typedef  TYPE_5__ ngx_http_module_t ;
typedef  TYPE_4__ ngx_http_core_loc_conf_t ;
struct TYPE_28__ {TYPE_4__** loc_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_7__ ngx_http_conf_ctx_t ;
struct TYPE_29__ {scalar_t__ cmd_type; TYPE_7__* ctx; TYPE_2__* cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_24__ {TYPE_1__** modules; } ;
struct TYPE_23__ {scalar_t__ type; size_t ctx_index; TYPE_5__* ctx; } ;
struct TYPE_22__ {int nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_21__ {size_t ctx_index; } ;
struct TYPE_20__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_HTTP_LIF_CONF ; 
 scalar_t__ NGX_HTTP_MODULE ; 
 scalar_t__ NGX_HTTP_SIF_CONF ; 
 scalar_t__ NGX_HTTP_SRV_CONF ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_array_push_n (TYPE_19__*,int) ; 
 char* ngx_conf_parse (TYPE_8__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_add_location (TYPE_8__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_14__ ngx_http_core_module ; 
 int ngx_http_max_module ; 
 char* ngx_http_rewrite_if_condition (TYPE_8__*,TYPE_4__*) ; 
 TYPE_10__ ngx_http_rewrite_module ; 
 int /*<<< orphan*/  ngx_http_script_if_code ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* stub1 (TYPE_8__*) ; 

__attribute__((used)) static char *
ngx_http_rewrite_if(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_rewrite_loc_conf_t  *lcf = conf;

    void                         *mconf;
    char                         *rv;
    u_char                       *elts;
    ngx_uint_t                    i;
    ngx_conf_t                    save;
    ngx_http_module_t            *module;
    ngx_http_conf_ctx_t          *ctx, *pctx;
    ngx_http_core_loc_conf_t     *clcf, *pclcf;
    ngx_http_script_if_code_t    *if_code;
    ngx_http_rewrite_loc_conf_t  *nlcf;

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

    pclcf = pctx->loc_conf[ngx_http_core_module.ctx_index];

    clcf = ctx->loc_conf[ngx_http_core_module.ctx_index];
    clcf->loc_conf = ctx->loc_conf;
    clcf->name = pclcf->name;
    clcf->noname = 1;

    if (ngx_http_add_location(cf, &pclcf->locations, clcf) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (ngx_http_rewrite_if_condition(cf, lcf) != NGX_CONF_OK) {
        return NGX_CONF_ERROR;
    }

    if_code = ngx_array_push_n(lcf->codes, sizeof(ngx_http_script_if_code_t));
    if (if_code == NULL) {
        return NGX_CONF_ERROR;
    }

    if_code->code = ngx_http_script_if_code;

    elts = lcf->codes->elts;


    /* the inner directives must be compiled to the same code array */

    nlcf = ctx->loc_conf[ngx_http_rewrite_module.ctx_index];
    nlcf->codes = lcf->codes;


    save = *cf;
    cf->ctx = ctx;

    if (cf->cmd_type == NGX_HTTP_SRV_CONF) {
        if_code->loc_conf = NULL;
        cf->cmd_type = NGX_HTTP_SIF_CONF;

    } else {
        if_code->loc_conf = ctx->loc_conf;
        cf->cmd_type = NGX_HTTP_LIF_CONF;
    }

    rv = ngx_conf_parse(cf, NULL);

    *cf = save;

    if (rv != NGX_CONF_OK) {
        return rv;
    }


    if (elts != lcf->codes->elts) {
        if_code = (ngx_http_script_if_code_t *)
                   ((u_char *) if_code + ((u_char *) lcf->codes->elts - elts));
    }

    if_code->next = (u_char *) lcf->codes->elts + lcf->codes->nelts
                                                - (u_char *) if_code;

    /* the code array belong to parent block */

    nlcf->codes = NULL;

    return NGX_CONF_OK;
}
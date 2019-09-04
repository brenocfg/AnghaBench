#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_20__ {int quote; scalar_t__ status; scalar_t__ ip; int /*<<< orphan*/  log; TYPE_7__* request; int /*<<< orphan*/ * sp; } ;
typedef  TYPE_4__ ngx_http_script_engine_t ;
typedef  int /*<<< orphan*/  (* ngx_http_script_code_pt ) (TYPE_4__*) ;
struct TYPE_21__ {int stack_size; int /*<<< orphan*/  log; TYPE_3__* codes; } ;
typedef  TYPE_6__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_22__ {scalar_t__ phase_handler; scalar_t__ loc_conf; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_23__ {TYPE_2__* ctx; } ;
typedef  TYPE_8__ ngx_http_core_srv_conf_t ;
struct TYPE_17__ {scalar_t__ location_rewrite_index; } ;
struct TYPE_24__ {TYPE_1__ phase_engine; } ;
typedef  TYPE_9__ ngx_http_core_main_conf_t ;
struct TYPE_19__ {scalar_t__ elts; } ;
struct TYPE_18__ {scalar_t__ loc_conf; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_6__* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* ngx_http_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_srv_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_rewrite_module ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_rewrite_handler(ngx_http_request_t *r)
{
    ngx_int_t                     index;
    ngx_http_script_code_pt       code;
    ngx_http_script_engine_t     *e;
    ngx_http_core_srv_conf_t     *cscf;
    ngx_http_core_main_conf_t    *cmcf;
    ngx_http_rewrite_loc_conf_t  *rlcf;

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);
    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);
    index = cmcf->phase_engine.location_rewrite_index;

    if (r->phase_handler == index && r->loc_conf == cscf->ctx->loc_conf) {
        /* skipping location rewrite phase for server null location */
        return NGX_DECLINED;
    }

    rlcf = ngx_http_get_module_loc_conf(r, ngx_http_rewrite_module);

    if (rlcf->codes == NULL) {
        return NGX_DECLINED;
    }

    e = ngx_pcalloc(r->pool, sizeof(ngx_http_script_engine_t));
    if (e == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    e->sp = ngx_pcalloc(r->pool,
                        rlcf->stack_size * sizeof(ngx_http_variable_value_t));
    if (e->sp == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    e->ip = rlcf->codes->elts;
    e->request = r;
    e->quote = 1;
    e->log = rlcf->log;
    e->status = NGX_DECLINED;

    while (*(uintptr_t *) e->ip) {
        code = *(ngx_http_script_code_pt *) e->ip;
        code(e);
    }

    return e->status;
}
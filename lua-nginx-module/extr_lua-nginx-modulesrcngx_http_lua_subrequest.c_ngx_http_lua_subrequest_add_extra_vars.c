#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_26__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_24__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_23__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {TYPE_2__ value; TYPE_1__ key; } ;
typedef  TYPE_5__ ngx_keyval_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_28__ {int valid; size_t len; int /*<<< orphan*/ * data; scalar_t__ no_cacheable; scalar_t__ not_found; } ;
typedef  TYPE_6__ ngx_http_variable_value_t ;
struct TYPE_29__ {int flags; size_t index; int /*<<< orphan*/  data; int /*<<< orphan*/  (* set_handler ) (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_7__ ngx_http_variable_t ;
struct TYPE_30__ {TYPE_3__* connection; TYPE_6__* variables; int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_31__ {int /*<<< orphan*/  variables_hash; } ;
typedef  TYPE_9__ ngx_http_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_hash_t ;
struct TYPE_22__ {scalar_t__ nelts; TYPE_5__* elts; } ;
typedef  TYPE_10__ ngx_array_t ;
struct TYPE_25__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_HTTP_VAR_CHANGEABLE ; 
 int NGX_HTTP_VAR_INDEXED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_7__* ngx_hash_find (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ngx_hash_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_9__* ngx_http_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_6__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_subrequest_add_extra_vars(ngx_http_request_t *sr,
    ngx_array_t *extra_vars)
{
    ngx_http_core_main_conf_t   *cmcf;
    ngx_http_variable_t         *v;
    ngx_http_variable_value_t   *vv;
    u_char                      *val;
    u_char                      *p;
    ngx_uint_t                   i, hash;
    ngx_str_t                    name;
    size_t                       len;
    ngx_hash_t                  *variables_hash;
    ngx_keyval_t                *var;

    /* set any extra variables that were passed to the subrequest */

    if (extra_vars == NULL || extra_vars->nelts == 0) {
        return NGX_OK;
    }

    cmcf = ngx_http_get_module_main_conf(sr, ngx_http_core_module);

    variables_hash = &cmcf->variables_hash;

    var = extra_vars->elts;

    for (i = 0; i < extra_vars->nelts; i++, var++) {
        /* copy the variable's name and value because they are allocated
         * by the lua VM */

        len = var->key.len + var->value.len;

        p = ngx_pnalloc(sr->pool, len);
        if (p == NULL) {
            return NGX_ERROR;
        }

        name.data = p;
        name.len = var->key.len;

        p = ngx_copy(p, var->key.data, var->key.len);

        hash = ngx_hash_strlow(name.data, name.data, name.len);

        val = p;
        len = var->value.len;

        ngx_memcpy(p, var->value.data, len);

        v = ngx_hash_find(variables_hash, hash, name.data, name.len);

        if (v) {
            if (!(v->flags & NGX_HTTP_VAR_CHANGEABLE)) {
                ngx_log_error(NGX_LOG_ERR, sr->connection->log, 0,
                              "variable \"%V\" not changeable", &name);
                return NGX_HTTP_INTERNAL_SERVER_ERROR;
            }

            if (v->set_handler) {
                vv = ngx_palloc(sr->pool, sizeof(ngx_http_variable_value_t));
                if (vv == NULL) {
                    return NGX_ERROR;
                }

                vv->valid = 1;
                vv->not_found = 0;
                vv->no_cacheable = 0;

                vv->data = val;
                vv->len = len;

                v->set_handler(sr, vv, v->data);

                ngx_log_debug2(NGX_LOG_DEBUG_HTTP, sr->connection->log, 0,
                               "variable \"%V\" set to value \"%v\"", &name,
                               vv);

                continue;
            }

            if (v->flags & NGX_HTTP_VAR_INDEXED) {
                vv = &sr->variables[v->index];

                vv->valid = 1;
                vv->not_found = 0;
                vv->no_cacheable = 0;

                vv->data = val;
                vv->len = len;

                ngx_log_debug2(NGX_LOG_DEBUG_HTTP, sr->connection->log, 0,
                               "variable \"%V\" set to value \"%v\"",
                               &name, vv);

                continue;
            }
        }

        ngx_log_error(NGX_LOG_ERR, sr->connection->log, 0,
                      "variable \"%V\" cannot be assigned a value (maybe you "
                      "forgot to define it first?) ", &name);

        return NGX_ERROR;
    }

    return NGX_OK;
}
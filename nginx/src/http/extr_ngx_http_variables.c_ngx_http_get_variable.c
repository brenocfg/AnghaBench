#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_26__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_27__ {int not_found; } ;
typedef  TYPE_5__ ngx_http_variable_value_t ;
struct TYPE_24__ {size_t len; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {int flags; scalar_t__ (* get_handler ) (TYPE_7__*,TYPE_5__*,uintptr_t) ;uintptr_t data; TYPE_2__ name; int /*<<< orphan*/  index; } ;
typedef  TYPE_6__ ngx_http_variable_t ;
struct TYPE_29__ {int /*<<< orphan*/  pool; TYPE_1__* connection; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_25__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_30__ {TYPE_3__ prefix_variables; int /*<<< orphan*/  variables_hash; } ;
typedef  TYPE_8__ ngx_http_core_main_conf_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int NGX_HTTP_VAR_INDEXED ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_hash_find (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_flushed_variable (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_variable_depth ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 TYPE_5__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (TYPE_7__*,TYPE_5__*,uintptr_t) ; 
 scalar_t__ stub2 (TYPE_7__*,TYPE_5__*,uintptr_t) ; 

ngx_http_variable_value_t *
ngx_http_get_variable(ngx_http_request_t *r, ngx_str_t *name, ngx_uint_t key)
{
    size_t                      len;
    ngx_uint_t                  i, n;
    ngx_http_variable_t        *v;
    ngx_http_variable_value_t  *vv;
    ngx_http_core_main_conf_t  *cmcf;

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    v = ngx_hash_find(&cmcf->variables_hash, key, name->data, name->len);

    if (v) {
        if (v->flags & NGX_HTTP_VAR_INDEXED) {
            return ngx_http_get_flushed_variable(r, v->index);
        }

        if (ngx_http_variable_depth == 0) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "cycle while evaluating variable \"%V\"", name);
            return NULL;
        }

        ngx_http_variable_depth--;

        vv = ngx_palloc(r->pool, sizeof(ngx_http_variable_value_t));

        if (vv && v->get_handler(r, vv, v->data) == NGX_OK) {
            ngx_http_variable_depth++;
            return vv;
        }

        ngx_http_variable_depth++;
        return NULL;
    }

    vv = ngx_palloc(r->pool, sizeof(ngx_http_variable_value_t));
    if (vv == NULL) {
        return NULL;
    }

    len = 0;

    v = cmcf->prefix_variables.elts;
    n = cmcf->prefix_variables.nelts;

    for (i = 0; i < cmcf->prefix_variables.nelts; i++) {
        if (name->len >= v[i].name.len && name->len > len
            && ngx_strncmp(name->data, v[i].name.data, v[i].name.len) == 0)
        {
            len = v[i].name.len;
            n = i;
        }
    }

    if (n != cmcf->prefix_variables.nelts) {
        if (v[n].get_handler(r, vv, (uintptr_t) name) == NGX_OK) {
            return vv;
        }

        return NULL;
    }

    vv->not_found = 1;

    return vv;
}
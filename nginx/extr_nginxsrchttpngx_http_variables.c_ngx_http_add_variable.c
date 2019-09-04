#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;
typedef  struct TYPE_21__   TYPE_17__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_25__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_22__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {int flags; TYPE_18__ name; scalar_t__ index; scalar_t__ data; int /*<<< orphan*/ * get_handler; int /*<<< orphan*/ * set_handler; } ;
typedef  TYPE_4__ ngx_http_variable_t ;
struct TYPE_27__ {TYPE_17__* variables_keys; } ;
typedef  TYPE_5__ ngx_http_core_main_conf_t ;
struct TYPE_24__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_28__ {TYPE_4__* value; TYPE_2__ key; } ;
typedef  TYPE_6__ ngx_hash_key_t ;
struct TYPE_29__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
struct TYPE_23__ {int nelts; TYPE_6__* elts; } ;
struct TYPE_21__ {TYPE_1__ keys; } ;

/* Variables and functions */
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_VAR_CHANGEABLE ; 
 int NGX_HTTP_VAR_PREFIX ; 
 int NGX_HTTP_VAR_WEAK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_hash_add_key (TYPE_17__*,TYPE_18__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_http_add_prefix_variable (TYPE_7__*,TYPE_3__*,int) ; 
 TYPE_5__* ngx_http_conf_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

ngx_http_variable_t *
ngx_http_add_variable(ngx_conf_t *cf, ngx_str_t *name, ngx_uint_t flags)
{
    ngx_int_t                   rc;
    ngx_uint_t                  i;
    ngx_hash_key_t             *key;
    ngx_http_variable_t        *v;
    ngx_http_core_main_conf_t  *cmcf;

    if (name->len == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid variable name \"$\"");
        return NULL;
    }

    if (flags & NGX_HTTP_VAR_PREFIX) {
        return ngx_http_add_prefix_variable(cf, name, flags);
    }

    cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

    key = cmcf->variables_keys->keys.elts;
    for (i = 0; i < cmcf->variables_keys->keys.nelts; i++) {
        if (name->len != key[i].key.len
            || ngx_strncasecmp(name->data, key[i].key.data, name->len) != 0)
        {
            continue;
        }

        v = key[i].value;

        if (!(v->flags & NGX_HTTP_VAR_CHANGEABLE)) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the duplicate \"%V\" variable", name);
            return NULL;
        }

        if (!(flags & NGX_HTTP_VAR_WEAK)) {
            v->flags &= ~NGX_HTTP_VAR_WEAK;
        }

        return v;
    }

    v = ngx_palloc(cf->pool, sizeof(ngx_http_variable_t));
    if (v == NULL) {
        return NULL;
    }

    v->name.len = name->len;
    v->name.data = ngx_pnalloc(cf->pool, name->len);
    if (v->name.data == NULL) {
        return NULL;
    }

    ngx_strlow(v->name.data, name->data, name->len);

    v->set_handler = NULL;
    v->get_handler = NULL;
    v->data = 0;
    v->flags = flags;
    v->index = 0;

    rc = ngx_hash_add_key(cmcf->variables_keys, &v->name, v, 0);

    if (rc == NGX_ERROR) {
        return NULL;
    }

    if (rc == NGX_BUSY) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "conflicting variable name \"%V\"", name);
        return NULL;
    }

    return v;
}
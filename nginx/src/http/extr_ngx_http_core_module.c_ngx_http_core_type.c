#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {char* data; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_15__ {TYPE_11__* types; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
struct TYPE_16__ {size_t key_hash; TYPE_2__* value; TYPE_2__ key; } ;
typedef  TYPE_4__ ngx_hash_key_t ;
struct TYPE_17__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_13__ {int nelts; TYPE_2__* elts; } ;
struct TYPE_12__ {size_t nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 TYPE_4__* ngx_array_push (TYPE_11__*) ; 
 char* ngx_conf_include (TYPE_5__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 size_t ngx_hash_strlow (char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 

__attribute__((used)) static char *
ngx_http_core_type(ngx_conf_t *cf, ngx_command_t *dummy, void *conf)
{
    ngx_http_core_loc_conf_t *clcf = conf;

    ngx_str_t       *value, *content_type, *old;
    ngx_uint_t       i, n, hash;
    ngx_hash_key_t  *type;

    value = cf->args->elts;

    if (ngx_strcmp(value[0].data, "include") == 0) {
        if (cf->args->nelts != 2) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid number of arguments"
                               " in \"include\" directive");
            return NGX_CONF_ERROR;
        }

        return ngx_conf_include(cf, dummy, conf);
    }

    content_type = ngx_palloc(cf->pool, sizeof(ngx_str_t));
    if (content_type == NULL) {
        return NGX_CONF_ERROR;
    }

    *content_type = value[0];

    for (i = 1; i < cf->args->nelts; i++) {

        hash = ngx_hash_strlow(value[i].data, value[i].data, value[i].len);

        type = clcf->types->elts;
        for (n = 0; n < clcf->types->nelts; n++) {
            if (ngx_strcmp(value[i].data, type[n].key.data) == 0) {
                old = type[n].value;
                type[n].value = content_type;

                ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                                   "duplicate extension \"%V\", "
                                   "content type: \"%V\", "
                                   "previous content type: \"%V\"",
                                   &value[i], content_type, old);
                goto next;
            }
        }


        type = ngx_array_push(clcf->types);
        if (type == NULL) {
            return NGX_CONF_ERROR;
        }

        type->key = value[i];
        type->key_hash = hash;
        type->value = content_type;

    next:
        continue;
    }

    return NGX_CONF_OK;
}
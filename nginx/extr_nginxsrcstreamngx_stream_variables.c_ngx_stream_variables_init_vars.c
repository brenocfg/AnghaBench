#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_24__ {uintptr_t data; int flags; size_t index; TYPE_14__ name; int /*<<< orphan*/ * get_handler; } ;
typedef  TYPE_6__ ngx_stream_variable_t ;
struct TYPE_20__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_19__ {size_t nelts; TYPE_6__* elts; } ;
struct TYPE_25__ {TYPE_5__* variables_keys; int /*<<< orphan*/  variables_hash_bucket_size; int /*<<< orphan*/  variables_hash_max_size; int /*<<< orphan*/  variables_hash; TYPE_2__ prefix_variables; TYPE_1__ variables; } ;
typedef  TYPE_7__ ngx_stream_core_main_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {TYPE_3__ key; TYPE_6__* value; } ;
typedef  TYPE_8__ ngx_hash_key_t ;
struct TYPE_27__ {char* name; int /*<<< orphan*/ * temp_pool; int /*<<< orphan*/  pool; int /*<<< orphan*/  bucket_size; int /*<<< orphan*/  max_size; int /*<<< orphan*/  key; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_9__ ngx_hash_init_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_conf_t ;
struct TYPE_22__ {size_t nelts; TYPE_8__* elts; } ;
struct TYPE_23__ {TYPE_4__ keys; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int NGX_STREAM_VAR_INDEXED ; 
 int NGX_STREAM_VAR_NOHASH ; 
 int NGX_STREAM_VAR_WEAK ; 
 scalar_t__ ngx_hash_init (TYPE_9__*,TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  ngx_hash_key ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_14__*) ; 
 TYPE_7__* ngx_stream_conf_get_module_main_conf (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

ngx_int_t
ngx_stream_variables_init_vars(ngx_conf_t *cf)
{
    size_t                        len;
    ngx_uint_t                    i, n;
    ngx_hash_key_t               *key;
    ngx_hash_init_t               hash;
    ngx_stream_variable_t        *v, *av, *pv;
    ngx_stream_core_main_conf_t  *cmcf;

    /* set the handlers for the indexed stream variables */

    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);

    v = cmcf->variables.elts;
    pv = cmcf->prefix_variables.elts;
    key = cmcf->variables_keys->keys.elts;

    for (i = 0; i < cmcf->variables.nelts; i++) {

        for (n = 0; n < cmcf->variables_keys->keys.nelts; n++) {

            av = key[n].value;

            if (v[i].name.len == key[n].key.len
                && ngx_strncmp(v[i].name.data, key[n].key.data, v[i].name.len)
                   == 0)
            {
                v[i].get_handler = av->get_handler;
                v[i].data = av->data;

                av->flags |= NGX_STREAM_VAR_INDEXED;
                v[i].flags = av->flags;

                av->index = i;

                if (av->get_handler == NULL
                    || (av->flags & NGX_STREAM_VAR_WEAK))
                {
                    break;
                }

                goto next;
            }
        }

        len = 0;
        av = NULL;

        for (n = 0; n < cmcf->prefix_variables.nelts; n++) {
            if (v[i].name.len >= pv[n].name.len && v[i].name.len > len
                && ngx_strncmp(v[i].name.data, pv[n].name.data, pv[n].name.len)
                   == 0)
            {
                av = &pv[n];
                len = pv[n].name.len;
            }
        }

        if (av) {
            v[i].get_handler = av->get_handler;
            v[i].data = (uintptr_t) &v[i].name;
            v[i].flags = av->flags;

            goto next;
         }

        if (v[i].get_handler == NULL) {
            ngx_log_error(NGX_LOG_EMERG, cf->log, 0,
                          "unknown \"%V\" variable", &v[i].name);
            return NGX_ERROR;
        }

    next:
        continue;
    }


    for (n = 0; n < cmcf->variables_keys->keys.nelts; n++) {
        av = key[n].value;

        if (av->flags & NGX_STREAM_VAR_NOHASH) {
            key[n].key.data = NULL;
        }
    }


    hash.hash = &cmcf->variables_hash;
    hash.key = ngx_hash_key;
    hash.max_size = cmcf->variables_hash_max_size;
    hash.bucket_size = cmcf->variables_hash_bucket_size;
    hash.name = "variables_hash";
    hash.pool = cf->pool;
    hash.temp_pool = NULL;

    if (ngx_hash_init(&hash, cmcf->variables_keys->keys.elts,
                      cmcf->variables_keys->keys.nelts)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    cmcf->variables_keys = NULL;

    return NGX_OK;
}
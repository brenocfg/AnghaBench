#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_16__ {int valid; int /*<<< orphan*/ * data; scalar_t__ len; scalar_t__ not_found; scalar_t__ no_cacheable; } ;
typedef  TYPE_4__ ngx_http_variable_value_t ;
struct TYPE_19__ {int /*<<< orphan*/  key; } ;
struct TYPE_13__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_14__ {TYPE_8__ node; TYPE_1__ str; } ;
struct TYPE_17__ {TYPE_2__ sn; scalar_t__ offset; TYPE_4__* value; } ;
typedef  TYPE_5__ ngx_http_geo_variable_value_node_t ;
struct TYPE_18__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  rbtree; int /*<<< orphan*/  temp_pool; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_http_geo_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 scalar_t__ ngx_align (scalar_t__,int) ; 
 int /*<<< orphan*/  ngx_crc32_long (int /*<<< orphan*/ ,scalar_t__) ; 
 void* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pstrdup (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rbtree_insert (int /*<<< orphan*/ *,TYPE_8__*) ; 
 scalar_t__ ngx_str_rbtree_lookup (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_http_variable_value_t *
ngx_http_geo_value(ngx_conf_t *cf, ngx_http_geo_conf_ctx_t *ctx,
    ngx_str_t *value)
{
    uint32_t                             hash;
    ngx_http_variable_value_t           *val;
    ngx_http_geo_variable_value_node_t  *gvvn;

    hash = ngx_crc32_long(value->data, value->len);

    gvvn = (ngx_http_geo_variable_value_node_t *)
               ngx_str_rbtree_lookup(&ctx->rbtree, value, hash);

    if (gvvn) {
        return gvvn->value;
    }

    val = ngx_palloc(ctx->pool, sizeof(ngx_http_variable_value_t));
    if (val == NULL) {
        return NULL;
    }

    val->len = value->len;
    val->data = ngx_pstrdup(ctx->pool, value);
    if (val->data == NULL) {
        return NULL;
    }

    val->valid = 1;
    val->no_cacheable = 0;
    val->not_found = 0;

    gvvn = ngx_palloc(ctx->temp_pool,
                      sizeof(ngx_http_geo_variable_value_node_t));
    if (gvvn == NULL) {
        return NULL;
    }

    gvvn->sn.node.key = hash;
    gvvn->sn.str.len = val->len;
    gvvn->sn.str.data = val->data;
    gvvn->value = val;
    gvvn->offset = 0;

    ngx_rbtree_insert(&ctx->rbtree, &gvvn->sn.node);

    ctx->data_size += ngx_align(sizeof(ngx_http_variable_value_t) + value->len,
                                sizeof(void *));

    return val;
}
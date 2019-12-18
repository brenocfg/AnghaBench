#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_16__ {int /*<<< orphan*/  tree; int /*<<< orphan*/  tree6; } ;
typedef  TYPE_6__ ngx_http_geo_conf_ctx_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  s6_addr; } ;
struct TYPE_13__ {TYPE_2__ mask; TYPE_1__ addr; } ;
struct TYPE_15__ {TYPE_4__ in; TYPE_3__ in6; } ;
struct TYPE_17__ {int family; TYPE_5__ u; } ;
typedef  TYPE_7__ ngx_cidr_t ;

/* Variables and functions */
#define  AF_INET6 128 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ngx_http_geo_value (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_radix128tree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_radix128tree_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_radix128tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 scalar_t__ ngx_radix32tree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_radix32tree_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_radix32tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static char *
ngx_http_geo_cidr_add(ngx_conf_t *cf, ngx_http_geo_conf_ctx_t *ctx,
    ngx_cidr_t *cidr, ngx_str_t *value, ngx_str_t *net)
{
    ngx_int_t                   rc;
    ngx_http_variable_value_t  *val, *old;

    val = ngx_http_geo_value(cf, ctx, value);

    if (val == NULL) {
        return NGX_CONF_ERROR;
    }

    switch (cidr->family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        rc = ngx_radix128tree_insert(ctx->tree6, cidr->u.in6.addr.s6_addr,
                                     cidr->u.in6.mask.s6_addr,
                                     (uintptr_t) val);

        if (rc == NGX_OK) {
            return NGX_CONF_OK;
        }

        if (rc == NGX_ERROR) {
            return NGX_CONF_ERROR;
        }

        /* rc == NGX_BUSY */

        old = (ngx_http_variable_value_t *)
                   ngx_radix128tree_find(ctx->tree6,
                                         cidr->u.in6.addr.s6_addr);

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
              "duplicate network \"%V\", value: \"%v\", old value: \"%v\"",
              net, val, old);

        rc = ngx_radix128tree_delete(ctx->tree6,
                                     cidr->u.in6.addr.s6_addr,
                                     cidr->u.in6.mask.s6_addr);

        if (rc == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid radix tree");
            return NGX_CONF_ERROR;
        }

        rc = ngx_radix128tree_insert(ctx->tree6, cidr->u.in6.addr.s6_addr,
                                     cidr->u.in6.mask.s6_addr,
                                     (uintptr_t) val);

        break;
#endif

    default: /* AF_INET */
        rc = ngx_radix32tree_insert(ctx->tree, cidr->u.in.addr,
                                    cidr->u.in.mask, (uintptr_t) val);

        if (rc == NGX_OK) {
            return NGX_CONF_OK;
        }

        if (rc == NGX_ERROR) {
            return NGX_CONF_ERROR;
        }

        /* rc == NGX_BUSY */

        old = (ngx_http_variable_value_t *)
                   ngx_radix32tree_find(ctx->tree, cidr->u.in.addr);

        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
              "duplicate network \"%V\", value: \"%v\", old value: \"%v\"",
              net, val, old);

        rc = ngx_radix32tree_delete(ctx->tree,
                                    cidr->u.in.addr, cidr->u.in.mask);

        if (rc == NGX_ERROR) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "invalid radix tree");
            return NGX_CONF_ERROR;
        }

        rc = ngx_radix32tree_insert(ctx->tree, cidr->u.in.addr,
                                    cidr->u.in.mask, (uintptr_t) val);

        break;
    }

    if (rc == NGX_OK) {
        return NGX_CONF_OK;
    }

    return NGX_CONF_ERROR;
}
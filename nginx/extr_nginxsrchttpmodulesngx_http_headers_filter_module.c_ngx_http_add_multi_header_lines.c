#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ len; } ;
struct TYPE_15__ {int hash; TYPE_3__ value; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ngx_table_elt_t ;
typedef  TYPE_3__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_14__ {int /*<<< orphan*/  headers; } ;
struct TYPE_17__ {TYPE_1__ headers_out; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_18__ {int offset; int /*<<< orphan*/  key; } ;
typedef  TYPE_5__ ngx_http_header_val_t ;
struct TYPE_19__ {int /*<<< orphan*/ * elts; } ;
typedef  TYPE_6__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__** ngx_array_push (TYPE_6__*) ; 
 TYPE_2__* ngx_list_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_add_multi_header_lines(ngx_http_request_t *r,
    ngx_http_header_val_t *hv, ngx_str_t *value)
{
    ngx_array_t      *pa;
    ngx_table_elt_t  *h, **ph;

    if (value->len == 0) {
        return NGX_OK;
    }

    pa = (ngx_array_t *) ((char *) &r->headers_out + hv->offset);

    if (pa->elts == NULL) {
        if (ngx_array_init(pa, r->pool, 1, sizeof(ngx_table_elt_t *)) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    h = ngx_list_push(&r->headers_out.headers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    h->hash = 1;
    h->key = hv->key;
    h->value = *value;

    ph = ngx_array_push(pa);
    if (ph == NULL) {
        return NGX_ERROR;
    }

    *ph = h;

    return NGX_OK;
}
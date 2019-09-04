#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  headers; } ;
struct TYPE_8__ {TYPE_1__ headers_out; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_9__ {int /*<<< orphan*/ * elts; } ;
typedef  TYPE_3__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** ngx_array_push (TYPE_3__*) ; 
 int /*<<< orphan*/ * ngx_list_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_copy_multi_header_lines(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_array_t      *pa;
    ngx_table_elt_t  *ho, **ph;

    pa = (ngx_array_t *) ((char *) &r->headers_out + offset);

    if (pa->elts == NULL) {
        if (ngx_array_init(pa, r->pool, 2, sizeof(ngx_table_elt_t *)) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    ho = ngx_list_push(&r->headers_out.headers);
    if (ho == NULL) {
        return NGX_ERROR;
    }

    *ho = *h;

    ph = ngx_array_push(pa);
    if (ph == NULL) {
        return NGX_ERROR;
    }

    *ph = ho;

    return NGX_OK;
}
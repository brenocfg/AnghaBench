#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_10__ {TYPE_5__ cookies; } ;
struct TYPE_11__ {scalar_t__ cacheable; TYPE_1__* conf; TYPE_2__ headers_in; } ;
typedef  TYPE_3__ ngx_http_upstream_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; TYPE_3__* upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  TYPE_5__ ngx_array_t ;
struct TYPE_9__ {int ignore_headers; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int NGX_HTTP_UPSTREAM_IGN_SET_COOKIE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_5__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** ngx_array_push (TYPE_5__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_set_cookie(ngx_http_request_t *r, ngx_table_elt_t *h,
    ngx_uint_t offset)
{
    ngx_array_t           *pa;
    ngx_table_elt_t      **ph;
    ngx_http_upstream_t   *u;

    u = r->upstream;
    pa = &u->headers_in.cookies;

    if (pa->elts == NULL) {
        if (ngx_array_init(pa, r->pool, 1, sizeof(ngx_table_elt_t *)) != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    ph = ngx_array_push(pa);
    if (ph == NULL) {
        return NGX_ERROR;
    }

    *ph = h;

#if (NGX_HTTP_CACHE)
    if (!(u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_SET_COOKIE)) {
        u->cacheable = 0;
    }
#endif

    return NGX_OK;
}
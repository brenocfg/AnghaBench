#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_table_elt_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_8__ {TYPE_4__ cache_control; } ;
struct TYPE_9__ {TYPE_1__ headers_in; } ;
typedef  TYPE_2__ ngx_http_upstream_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; TYPE_2__* upstream; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  TYPE_4__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** ngx_array_push (TYPE_4__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_process_cache_control(ngx_http_request_t *r,
    ngx_table_elt_t *h, ngx_uint_t offset)
{
    ngx_array_t          *pa;
    ngx_table_elt_t     **ph;
    ngx_http_upstream_t  *u;

    u = r->upstream;
    pa = &u->headers_in.cache_control;

    if (pa->elts == NULL) {
        if (ngx_array_init(pa, r->pool, 2, sizeof(ngx_table_elt_t *)) != NGX_OK)
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
    {
    u_char     *p, *start, *last;
    ngx_int_t   n;

    if (u->conf->ignore_headers & NGX_HTTP_UPSTREAM_IGN_CACHE_CONTROL) {
        return NGX_OK;
    }

    if (r->cache == NULL) {
        return NGX_OK;
    }

    if (r->cache->valid_sec != 0 && u->headers_in.x_accel_expires != NULL) {
        return NGX_OK;
    }

    start = h->value.data;
    last = start + h->value.len;

    if (ngx_strlcasestrn(start, last, (u_char *) "no-cache", 8 - 1) != NULL
        || ngx_strlcasestrn(start, last, (u_char *) "no-store", 8 - 1) != NULL
        || ngx_strlcasestrn(start, last, (u_char *) "private", 7 - 1) != NULL)
    {
        u->cacheable = 0;
        return NGX_OK;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "s-maxage=", 9 - 1);
    offset = 9;

    if (p == NULL) {
        p = ngx_strlcasestrn(start, last, (u_char *) "max-age=", 8 - 1);
        offset = 8;
    }

    if (p) {
        n = 0;

        for (p += offset; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        if (n == 0) {
            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->valid_sec = ngx_time() + n;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "stale-while-revalidate=",
                         23 - 1);

    if (p) {
        n = 0;

        for (p += 23; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->updating_sec = n;
        r->cache->error_sec = n;
    }

    p = ngx_strlcasestrn(start, last, (u_char *) "stale-if-error=", 15 - 1);

    if (p) {
        n = 0;

        for (p += 15; p < last; p++) {
            if (*p == ',' || *p == ';' || *p == ' ') {
                break;
            }

            if (*p >= '0' && *p <= '9') {
                n = n * 10 + (*p - '0');
                continue;
            }

            u->cacheable = 0;
            return NGX_OK;
        }

        r->cache->error_sec = n;
    }
    }
#endif

    return NGX_OK;
}
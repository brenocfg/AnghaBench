#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_pool_cleanup_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; TYPE_4__* cache; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_12__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ ngx_http_file_cache_t ;
struct TYPE_13__ {TYPE_3__* file_cache; } ;
typedef  TYPE_4__ ngx_http_cache_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_file_cache_cleanup ; 
 scalar_t__ ngx_http_file_cache_exists (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ ngx_http_file_cache_name (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_file_cache_create(ngx_http_request_t *r)
{
    ngx_http_cache_t       *c;
    ngx_pool_cleanup_t     *cln;
    ngx_http_file_cache_t  *cache;

    c = r->cache;
    cache = c->file_cache;

    cln = ngx_pool_cleanup_add(r->pool, 0);
    if (cln == NULL) {
        return NGX_ERROR;
    }

    cln->handler = ngx_http_file_cache_cleanup;
    cln->data = c;

    if (ngx_http_file_cache_exists(cache, c) == NGX_ERROR) {
        return NGX_ERROR;
    }

    if (ngx_http_file_cache_name(r, cache->path) != NGX_OK) {
        return NGX_ERROR;
    }

    return NGX_OK;
}
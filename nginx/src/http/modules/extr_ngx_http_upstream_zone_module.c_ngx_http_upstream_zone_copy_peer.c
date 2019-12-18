#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_sockaddr_t ;
typedef  int /*<<< orphan*/  ngx_slab_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/ * shpool; } ;
typedef  TYPE_3__ ngx_http_upstream_rr_peers_t ;
struct TYPE_13__ {int len; TYPE_4__* data; } ;
struct TYPE_12__ {int len; TYPE_4__* data; } ;
struct TYPE_15__ {int socklen; struct TYPE_15__* sockaddr; TYPE_2__ name; TYPE_1__ server; } ;
typedef  TYPE_4__ ngx_http_upstream_rr_peer_t ;

/* Variables and functions */
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_4__*,TYPE_4__*,int) ; 
 TYPE_4__* ngx_slab_alloc_locked (int /*<<< orphan*/ *,int) ; 
 void* ngx_slab_calloc_locked (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_slab_free_locked (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static ngx_http_upstream_rr_peer_t *
ngx_http_upstream_zone_copy_peer(ngx_http_upstream_rr_peers_t *peers,
    ngx_http_upstream_rr_peer_t *src)
{
    ngx_slab_pool_t              *pool;
    ngx_http_upstream_rr_peer_t  *dst;

    pool = peers->shpool;

    dst = ngx_slab_calloc_locked(pool, sizeof(ngx_http_upstream_rr_peer_t));
    if (dst == NULL) {
        return NULL;
    }

    if (src) {
        ngx_memcpy(dst, src, sizeof(ngx_http_upstream_rr_peer_t));
        dst->sockaddr = NULL;
        dst->name.data = NULL;
        dst->server.data = NULL;
    }

    dst->sockaddr = ngx_slab_calloc_locked(pool, sizeof(ngx_sockaddr_t));
    if (dst->sockaddr == NULL) {
        goto failed;
    }

    dst->name.data = ngx_slab_calloc_locked(pool, NGX_SOCKADDR_STRLEN);
    if (dst->name.data == NULL) {
        goto failed;
    }

    if (src) {
        ngx_memcpy(dst->sockaddr, src->sockaddr, src->socklen);
        ngx_memcpy(dst->name.data, src->name.data, src->name.len);

        dst->server.data = ngx_slab_alloc_locked(pool, src->server.len);
        if (dst->server.data == NULL) {
            goto failed;
        }

        ngx_memcpy(dst->server.data, src->server.data, src->server.len);
    }

    return dst;

failed:

    if (dst->server.data) {
        ngx_slab_free_locked(pool, dst->server.data);
    }

    if (dst->name.data) {
        ngx_slab_free_locked(pool, dst->name.data);
    }

    if (dst->sockaddr) {
        ngx_slab_free_locked(pool, dst->sockaddr);
    }

    ngx_slab_free_locked(pool, dst);

    return NULL;
}
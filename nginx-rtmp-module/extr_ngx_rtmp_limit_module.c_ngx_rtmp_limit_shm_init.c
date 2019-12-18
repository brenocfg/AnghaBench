#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ngx_slab_pool_t ;
struct TYPE_4__ {scalar_t__ addr; } ;
struct TYPE_5__ {scalar_t__* data; TYPE_1__ shm; } ;
typedef  TYPE_2__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__* ngx_slab_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_limit_shm_init(ngx_shm_zone_t *shm_zone, void *data)
{
    ngx_slab_pool_t    *shpool;
    uint32_t           *nconn;

    if (data) {
        shm_zone->data = data;
        return NGX_OK;
    }

    shpool = (ngx_slab_pool_t *) shm_zone->shm.addr;

    nconn = ngx_slab_alloc(shpool, 4);
    if (nconn == NULL) {
        return NGX_ERROR;
    }

    *nconn = 0;

    shm_zone->data = nconn;

    return NGX_OK;
}
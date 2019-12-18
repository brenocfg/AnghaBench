#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* large; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_pool_t ;
struct TYPE_7__ {struct TYPE_7__* next; void* alloc; } ;
typedef  TYPE_2__ ngx_pool_large_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_free (void*) ; 
 void* ngx_memalign (size_t,size_t,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_palloc_small (TYPE_1__*,int,int) ; 

void *
ngx_pmemalign(ngx_pool_t *pool, size_t size, size_t alignment)
{
    void              *p;
    ngx_pool_large_t  *large;

    p = ngx_memalign(alignment, size, pool->log);
    if (p == NULL) {
        return NULL;
    }

    large = ngx_palloc_small(pool, sizeof(ngx_pool_large_t), 1);
    if (large == NULL) {
        ngx_free(p);
        return NULL;
    }

    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_10__ {TYPE_3__* next; } ;
struct TYPE_11__ {int pfree; TYPE_1__ free; TYPE_3__* pages; TYPE_3__* last; } ;
typedef  TYPE_2__ ngx_slab_pool_t ;
struct TYPE_12__ {int slab; uintptr_t prev; struct TYPE_12__* next; } ;
typedef  TYPE_3__ ngx_slab_page_t ;

/* Variables and functions */
 scalar_t__ NGX_SLAB_PAGE ; 
 scalar_t__ NGX_SLAB_PAGE_FREE ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 TYPE_3__* ngx_slab_page_prev (TYPE_3__*) ; 
 scalar_t__ ngx_slab_page_type (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_slab_free_pages(ngx_slab_pool_t *pool, ngx_slab_page_t *page,
    ngx_uint_t pages)
{
    ngx_slab_page_t  *prev, *join;

    pool->pfree += pages;

    page->slab = pages--;

    if (pages) {
        ngx_memzero(&page[1], pages * sizeof(ngx_slab_page_t));
    }

    if (page->next) {
        prev = ngx_slab_page_prev(page);
        prev->next = page->next;
        page->next->prev = page->prev;
    }

    join = page + page->slab;

    if (join < pool->last) {

        if (ngx_slab_page_type(join) == NGX_SLAB_PAGE) {

            if (join->next != NULL) {
                pages += join->slab;
                page->slab += join->slab;

                prev = ngx_slab_page_prev(join);
                prev->next = join->next;
                join->next->prev = join->prev;

                join->slab = NGX_SLAB_PAGE_FREE;
                join->next = NULL;
                join->prev = NGX_SLAB_PAGE;
            }
        }
    }

    if (page > pool->pages) {
        join = page - 1;

        if (ngx_slab_page_type(join) == NGX_SLAB_PAGE) {

            if (join->slab == NGX_SLAB_PAGE_FREE) {
                join = ngx_slab_page_prev(join);
            }

            if (join->next != NULL) {
                pages += join->slab;
                join->slab += page->slab;

                prev = ngx_slab_page_prev(join);
                prev->next = join->next;
                join->next->prev = join->prev;

                page->slab = NGX_SLAB_PAGE_FREE;
                page->next = NULL;
                page->prev = NGX_SLAB_PAGE;

                page = join;
            }
        }
    }

    if (pages) {
        page[pages].prev = (uintptr_t) page;
    }

    page->prev = (uintptr_t) &pool->free;
    page->next = pool->free.next;

    page->next->prev = (uintptr_t) page;

    pool->free.next = page;
}
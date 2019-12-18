#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct page_cache_descr* tail; struct page_cache_descr* head; } ;
struct page_cache {TYPE_1__ replaceQ; } ;
struct rrdengine_instance {struct page_cache pg_cache; } ;
struct rrdeng_page_descr {struct page_cache_descr* pg_cache_descr; } ;
struct page_cache_descr {struct page_cache_descr* next; struct page_cache_descr* prev; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void pg_cache_replaceQ_delete_unsafe(struct rrdengine_instance *ctx,
                                                   struct rrdeng_page_descr *descr)
{
    struct page_cache *pg_cache = &ctx->pg_cache;
    struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr, *prev, *next;

    prev = pg_cache_descr->prev;
    next = pg_cache_descr->next;

    if (likely(NULL != prev)) {
        prev->next = next;
    }
    if (likely(NULL != next)) {
        next->prev = prev;
    }
    if (unlikely(pg_cache_descr == pg_cache->replaceQ.head)) {
        pg_cache->replaceQ.head = next;
    }
    if (unlikely(pg_cache_descr == pg_cache->replaceQ.tail)) {
        pg_cache->replaceQ.tail = prev;
    }
    pg_cache_descr->prev = pg_cache_descr->next = NULL;
}
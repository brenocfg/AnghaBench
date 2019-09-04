#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ allocated; int active; int free; int closed; unsigned int bucket; int /*<<< orphan*/  id; int /*<<< orphan*/  version; struct TYPE_8__* next; } ;
typedef  TYPE_1__ store_page ;
struct TYPE_9__ {scalar_t__ page_size; scalar_t__ page_free; TYPE_1__** page_buckets; TYPE_1__* page_freelist; TYPE_1__** free_page_buckets; } ;
typedef  TYPE_2__ store_engine ;

/* Variables and functions */
 int /*<<< orphan*/  E_DEBUG (char*,...) ; 
 int /*<<< orphan*/  STAT_INCR (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _next_version (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  extstore_run_maint (TYPE_2__*) ; 
 int /*<<< orphan*/  page_allocs ; 

__attribute__((used)) static store_page *_allocate_page(store_engine *e, unsigned int bucket,
        unsigned int free_bucket) {
    assert(!e->page_buckets[bucket] || e->page_buckets[bucket]->allocated == e->page_size);
    store_page *tmp = NULL;
    // if a specific free bucket was requested, check there first
    if (free_bucket != 0 && e->free_page_buckets[free_bucket] != NULL) {
        assert(e->page_free > 0);
        tmp = e->free_page_buckets[free_bucket];
        e->free_page_buckets[free_bucket] = tmp->next;
    }
    // failing that, try the global list.
    if (tmp == NULL && e->page_freelist != NULL) {
        tmp = e->page_freelist;
        e->page_freelist = tmp->next;
    }
    E_DEBUG("EXTSTORE: allocating new page\n");
    // page_freelist can be empty if the only free pages are specialized and
    // we didn't just request one.
    if (e->page_free > 0 && tmp != NULL) {
        tmp->next = e->page_buckets[bucket];
        e->page_buckets[bucket] = tmp;
        tmp->active = true;
        tmp->free = false;
        tmp->closed = false;
        tmp->version = _next_version(e);
        tmp->bucket = bucket;
        e->page_free--;
        STAT_INCR(e, page_allocs, 1);
    } else {
        extstore_run_maint(e);
    }
    if (tmp)
        E_DEBUG("EXTSTORE: got page %u\n", tmp->id);
    return tmp;
}
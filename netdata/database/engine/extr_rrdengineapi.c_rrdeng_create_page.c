#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct rrdengine_instance {int dummy; } ;
struct rrdeng_page_descr {struct page_cache_descr* pg_cache_descr; int /*<<< orphan*/ * id; } ;
struct page_cache_descr {int flags; int refcnt; void* page; } ;

/* Variables and functions */
 int D_RRDENGINE ; 
 int /*<<< orphan*/  RRDENG_BLOCK_SIZE ; 
 int RRD_PAGE_DIRTY ; 
 int RRD_PAGE_POPULATED ; 
 int /*<<< orphan*/  debug (int,char*) ; 
 int debug_flags ; 
 void* mallocz (int /*<<< orphan*/ ) ; 
 struct rrdeng_page_descr* pg_cache_create_descr () ; 
 int /*<<< orphan*/  print_page_cache_descr (struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_lock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_unlock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 scalar_t__ unlikely (int) ; 

void *rrdeng_create_page(struct rrdengine_instance *ctx, uuid_t *id, struct rrdeng_page_descr **ret_descr)
{
    struct rrdeng_page_descr *descr;
    struct page_cache_descr *pg_cache_descr;
    void *page;
    /* TODO: check maximum number of pages in page cache limit */

    descr = pg_cache_create_descr();
    descr->id = id; /* TODO: add page type: metric, log, something? */
    page = mallocz(RRDENG_BLOCK_SIZE); /*TODO: add page size */
    rrdeng_page_descr_mutex_lock(ctx, descr);
    pg_cache_descr = descr->pg_cache_descr;
    pg_cache_descr->page = page;
    pg_cache_descr->flags = RRD_PAGE_DIRTY /*| RRD_PAGE_LOCKED */ | RRD_PAGE_POPULATED /* | BEING_COLLECTED */;
    pg_cache_descr->refcnt = 1;

    debug(D_RRDENGINE, "Created new page:");
    if (unlikely(debug_flags & D_RRDENGINE))
        print_page_cache_descr(descr);
    rrdeng_page_descr_mutex_unlock(ctx, descr);
    *ret_descr = descr;
    return page;
}
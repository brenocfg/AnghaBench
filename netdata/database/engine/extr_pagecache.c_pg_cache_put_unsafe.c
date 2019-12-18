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
struct rrdeng_page_descr {struct page_cache_descr* pg_cache_descr; } ;
struct page_cache_descr {scalar_t__ refcnt; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RRD_PAGE_LOCKED ; 
 int /*<<< orphan*/  pg_cache_wake_up_waiters_unsafe (struct rrdeng_page_descr*) ; 

void pg_cache_put_unsafe(struct rrdeng_page_descr *descr)
{
    struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr;

    pg_cache_descr->flags &= ~RRD_PAGE_LOCKED;
    if (0 == --pg_cache_descr->refcnt) {
        pg_cache_wake_up_waiters_unsafe(descr);
    }
}
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
struct page_cache_descr {int flags; scalar_t__ refcnt; } ;

/* Variables and functions */
 int RRD_PAGE_LOCKED ; 
 int RRD_PAGE_READ_PENDING ; 

int pg_cache_can_get_unsafe(struct rrdeng_page_descr *descr, int exclusive_access)
{
    struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr;

    if ((pg_cache_descr->flags & (RRD_PAGE_LOCKED | RRD_PAGE_READ_PENDING)) ||
        (exclusive_access && pg_cache_descr->refcnt)) {
        return 0;
    }

    return 1;
}
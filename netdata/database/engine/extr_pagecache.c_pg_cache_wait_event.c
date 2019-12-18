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
struct rrdengine_instance {int dummy; } ;
struct rrdeng_page_descr {struct page_cache_descr* pg_cache_descr; } ;
struct page_cache_descr {unsigned long flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  pg_cache_wait_event_unsafe (struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_lock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrdeng_page_descr_mutex_unlock (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 

unsigned long pg_cache_wait_event(struct rrdengine_instance *ctx, struct rrdeng_page_descr *descr)
{
    struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr;
    unsigned long flags;

    rrdeng_page_descr_mutex_lock(ctx, descr);
    pg_cache_wait_event_unsafe(descr);
    flags = pg_cache_descr->flags;
    rrdeng_page_descr_mutex_unlock(ctx, descr);

    return flags;
}
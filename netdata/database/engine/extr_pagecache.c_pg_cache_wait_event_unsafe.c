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
struct page_cache_descr {int /*<<< orphan*/  waiters; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  uv_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pg_cache_wait_event_unsafe(struct rrdeng_page_descr *descr)
{
    struct page_cache_descr *pg_cache_descr = descr->pg_cache_descr;

    ++pg_cache_descr->waiters;
    uv_cond_wait(&pg_cache_descr->cond, &pg_cache_descr->mutex);
    --pg_cache_descr->waiters;
}
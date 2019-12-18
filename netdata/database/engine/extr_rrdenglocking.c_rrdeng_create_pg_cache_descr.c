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
struct TYPE_2__ {int /*<<< orphan*/  page_cache_descriptors; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct page_cache_descr {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; scalar_t__ waiters; scalar_t__ refcnt; int /*<<< orphan*/ * next; int /*<<< orphan*/  prev; scalar_t__ flags; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct page_cache_descr* mallocz (int) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ uv_cond_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_mutex_init (int /*<<< orphan*/ *) ; 

struct page_cache_descr *rrdeng_create_pg_cache_descr(struct rrdengine_instance *ctx)
{
    struct page_cache_descr *pg_cache_descr;

    pg_cache_descr = mallocz(sizeof(*pg_cache_descr));
    rrd_stat_atomic_add(&ctx->stats.page_cache_descriptors, 1);
    pg_cache_descr->page = NULL;
    pg_cache_descr->flags = 0;
    pg_cache_descr->prev = pg_cache_descr->next = NULL;
    pg_cache_descr->refcnt = 0;
    pg_cache_descr->waiters = 0;
    assert(0 == uv_cond_init(&pg_cache_descr->cond));
    assert(0 == uv_mutex_init(&pg_cache_descr->mutex));

    return pg_cache_descr;
}
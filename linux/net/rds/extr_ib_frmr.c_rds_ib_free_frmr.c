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
struct rds_ib_mr_pool {int max_free_pinned; int max_items; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  dirty_count; int /*<<< orphan*/  free_pinned; int /*<<< orphan*/  free_list; int /*<<< orphan*/  drop_list; } ;
struct rds_ib_mr {int /*<<< orphan*/  sg_len; int /*<<< orphan*/  llnode; struct rds_ib_mr_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rds_ib_mr_wq ; 

__attribute__((used)) static void rds_ib_free_frmr(struct rds_ib_mr *ibmr, bool drop)
{
	struct rds_ib_mr_pool *pool = ibmr->pool;

	if (drop)
		llist_add(&ibmr->llnode, &pool->drop_list);
	else
		llist_add(&ibmr->llnode, &pool->free_list);
	atomic_add(ibmr->sg_len, &pool->free_pinned);
	atomic_inc(&pool->dirty_count);

	/* If we've pinned too many pages, request a flush */
	if (atomic_read(&pool->free_pinned) >= pool->max_free_pinned ||
	    atomic_read(&pool->dirty_count) >= pool->max_items / 5)
		queue_delayed_work(rds_ib_mr_wq, &pool->flush_worker, 10);
}
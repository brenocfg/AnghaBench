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
struct rds_ib_mr_pool {int max_free_pinned; int max_items; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  dirty_count; int /*<<< orphan*/  free_pinned; } ;
struct rds_ib_mr {int /*<<< orphan*/  sg_len; struct rds_ib_device* device; struct rds_ib_mr_pool* pool; } ;
struct rds_ib_device {scalar_t__ use_fastreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rds_ib_dev_put (struct rds_ib_device*) ; 
 int /*<<< orphan*/  rds_ib_flush_mr_pool (struct rds_ib_mr_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_free_fmr_list (struct rds_ib_mr*) ; 
 int /*<<< orphan*/  rds_ib_free_frmr_list (struct rds_ib_mr*) ; 
 int /*<<< orphan*/  rds_ib_mr_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ) ; 

void rds_ib_free_mr(void *trans_private, int invalidate)
{
	struct rds_ib_mr *ibmr = trans_private;
	struct rds_ib_mr_pool *pool = ibmr->pool;
	struct rds_ib_device *rds_ibdev = ibmr->device;

	rdsdebug("RDS/IB: free_mr nents %u\n", ibmr->sg_len);

	/* Return it to the pool's free list */
	if (rds_ibdev->use_fastreg)
		rds_ib_free_frmr_list(ibmr);
	else
		rds_ib_free_fmr_list(ibmr);

	atomic_add(ibmr->sg_len, &pool->free_pinned);
	atomic_inc(&pool->dirty_count);

	/* If we've pinned too many pages, request a flush */
	if (atomic_read(&pool->free_pinned) >= pool->max_free_pinned ||
	    atomic_read(&pool->dirty_count) >= pool->max_items / 5)
		queue_delayed_work(rds_ib_mr_wq, &pool->flush_worker, 10);

	if (invalidate) {
		if (likely(!in_interrupt())) {
			rds_ib_flush_mr_pool(pool, 0, NULL);
		} else {
			/* We get here if the user created a MR marked
			 * as use_once and invalidate at the same time.
			 */
			queue_delayed_work(rds_ib_mr_wq,
					   &pool->flush_worker, 10);
		}
	}

	rds_ib_dev_put(rds_ibdev);
}
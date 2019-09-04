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
struct rds_ib_mr_pool {int max_items_soft; scalar_t__ max_items; scalar_t__ pool_type; int /*<<< orphan*/  item_count; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  dirty_count; } ;
struct rds_ib_mr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct rds_ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ RDS_IB_MR_8K_POOL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rds_ib_flush_mr_pool (struct rds_ib_mr_pool*,int /*<<< orphan*/ ,struct rds_ib_mr**) ; 
 int /*<<< orphan*/  rds_ib_mr_wq ; 
 struct rds_ib_mr* rds_ib_reuse_mr (struct rds_ib_mr_pool*) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_rdma_mr_1m_pool_depleted ; 
 int /*<<< orphan*/  s_ib_rdma_mr_1m_pool_wait ; 
 int /*<<< orphan*/  s_ib_rdma_mr_8k_pool_depleted ; 
 int /*<<< orphan*/  s_ib_rdma_mr_8k_pool_wait ; 

struct rds_ib_mr *rds_ib_try_reuse_ibmr(struct rds_ib_mr_pool *pool)
{
	struct rds_ib_mr *ibmr = NULL;
	int iter = 0;

	if (atomic_read(&pool->dirty_count) >= pool->max_items_soft / 10)
		queue_delayed_work(rds_ib_mr_wq, &pool->flush_worker, 10);

	while (1) {
		ibmr = rds_ib_reuse_mr(pool);
		if (ibmr)
			return ibmr;

		if (atomic_inc_return(&pool->item_count) <= pool->max_items)
			break;

		atomic_dec(&pool->item_count);

		if (++iter > 2) {
			if (pool->pool_type == RDS_IB_MR_8K_POOL)
				rds_ib_stats_inc(s_ib_rdma_mr_8k_pool_depleted);
			else
				rds_ib_stats_inc(s_ib_rdma_mr_1m_pool_depleted);
			return ERR_PTR(-EAGAIN);
		}

		/* We do have some empty MRs. Flush them out. */
		if (pool->pool_type == RDS_IB_MR_8K_POOL)
			rds_ib_stats_inc(s_ib_rdma_mr_8k_pool_wait);
		else
			rds_ib_stats_inc(s_ib_rdma_mr_1m_pool_wait);

		rds_ib_flush_mr_pool(pool, 0, &ibmr);
		if (ibmr)
			return ibmr;
	}

	return ibmr;
}
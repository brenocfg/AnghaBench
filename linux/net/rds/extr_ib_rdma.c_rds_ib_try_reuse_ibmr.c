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
struct rds_ib_mr_pool {scalar_t__ max_items; scalar_t__ pool_type; int /*<<< orphan*/  item_count; } ;
struct rds_ib_mr {int dummy; } ;

/* Variables and functions */
 scalar_t__ RDS_IB_MR_8K_POOL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_flush_mr_pool (struct rds_ib_mr_pool*,int /*<<< orphan*/ ,struct rds_ib_mr**) ; 
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
			break;
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

	return NULL;
}
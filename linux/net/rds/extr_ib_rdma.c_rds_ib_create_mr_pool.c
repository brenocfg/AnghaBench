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
struct TYPE_2__ {int max_pages; int /*<<< orphan*/  page_shift; int /*<<< orphan*/  max_maps; } ;
struct rds_ib_mr_pool {int pool_type; int max_items; int max_free_pinned; int max_items_soft; int /*<<< orphan*/  use_fastreg; TYPE_1__ fmr_attr; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  flush_wait; int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  clean_lock; int /*<<< orphan*/  clean_list; int /*<<< orphan*/  drop_list; int /*<<< orphan*/  free_list; } ;
struct rds_ib_device {int max_1m_mrs; int max_8k_mrs; int max_mrs; int /*<<< orphan*/  use_fastreg; int /*<<< orphan*/  fmr_max_remaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rds_ib_mr_pool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int RDS_IB_MR_1M_POOL ; 
 int RDS_MR_1M_MSG_SIZE ; 
 int RDS_MR_8K_MSG_SIZE ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct rds_ib_mr_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_mr_pool_flush_worker ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rds_ib_mr_pool *rds_ib_create_mr_pool(struct rds_ib_device *rds_ibdev,
					     int pool_type)
{
	struct rds_ib_mr_pool *pool;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return ERR_PTR(-ENOMEM);

	pool->pool_type = pool_type;
	init_llist_head(&pool->free_list);
	init_llist_head(&pool->drop_list);
	init_llist_head(&pool->clean_list);
	spin_lock_init(&pool->clean_lock);
	mutex_init(&pool->flush_lock);
	init_waitqueue_head(&pool->flush_wait);
	INIT_DELAYED_WORK(&pool->flush_worker, rds_ib_mr_pool_flush_worker);

	if (pool_type == RDS_IB_MR_1M_POOL) {
		/* +1 allows for unaligned MRs */
		pool->fmr_attr.max_pages = RDS_MR_1M_MSG_SIZE + 1;
		pool->max_items = rds_ibdev->max_1m_mrs;
	} else {
		/* pool_type == RDS_IB_MR_8K_POOL */
		pool->fmr_attr.max_pages = RDS_MR_8K_MSG_SIZE + 1;
		pool->max_items = rds_ibdev->max_8k_mrs;
	}

	pool->max_free_pinned = pool->max_items * pool->fmr_attr.max_pages / 4;
	pool->fmr_attr.max_maps = rds_ibdev->fmr_max_remaps;
	pool->fmr_attr.page_shift = PAGE_SHIFT;
	pool->max_items_soft = rds_ibdev->max_mrs * 3 / 4;
	pool->use_fastreg = rds_ibdev->use_fastreg;

	return pool;
}
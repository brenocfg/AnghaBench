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
struct rds_info_rdma_connection {int /*<<< orphan*/  rdma_mr_size; int /*<<< orphan*/  rdma_mr_max; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_pages; } ;
struct rds_ib_mr_pool {TYPE_1__ fmr_attr; int /*<<< orphan*/  max_items; } ;
struct rds_ib_device {struct rds_ib_mr_pool* mr_1m_pool; } ;

/* Variables and functions */

void rds_ib_get_mr_info(struct rds_ib_device *rds_ibdev, struct rds_info_rdma_connection *iinfo)
{
	struct rds_ib_mr_pool *pool_1m = rds_ibdev->mr_1m_pool;

	iinfo->rdma_mr_max = pool_1m->max_items;
	iinfo->rdma_mr_size = pool_1m->fmr_attr.max_pages;
}
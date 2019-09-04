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
struct TYPE_2__ {scalar_t__ max_maps; } ;
struct rds_ib_mr_pool {int /*<<< orphan*/  free_list; int /*<<< orphan*/  drop_list; TYPE_1__ fmr_attr; } ;
struct rds_ib_mr {scalar_t__ remap_count; int /*<<< orphan*/  llnode; struct rds_ib_mr_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rds_ib_free_fmr_list(struct rds_ib_mr *ibmr)
{
	struct rds_ib_mr_pool *pool = ibmr->pool;

	if (ibmr->remap_count >= pool->fmr_attr.max_maps)
		llist_add(&ibmr->llnode, &pool->drop_list);
	else
		llist_add(&ibmr->llnode, &pool->free_list);
}
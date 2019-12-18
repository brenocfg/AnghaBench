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
struct rds_ib_mr_pool {int /*<<< orphan*/  free_list; int /*<<< orphan*/  drop_list; } ;
struct rds_ib_frmr {scalar_t__ fr_state; } ;
struct TYPE_2__ {struct rds_ib_frmr frmr; } ;
struct rds_ib_mr {int /*<<< orphan*/  llnode; TYPE_1__ u; struct rds_ib_mr_pool* pool; } ;

/* Variables and functions */
 scalar_t__ FRMR_IS_STALE ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void rds_ib_free_frmr_list(struct rds_ib_mr *ibmr)
{
	struct rds_ib_mr_pool *pool = ibmr->pool;
	struct rds_ib_frmr *frmr = &ibmr->u.frmr;

	if (frmr->fr_state == FRMR_IS_STALE)
		llist_add(&ibmr->llnode, &pool->drop_list);
	else
		llist_add(&ibmr->llnode, &pool->free_list);
}
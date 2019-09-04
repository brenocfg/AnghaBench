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
struct rds_ib_mr_pool {int /*<<< orphan*/  free_pinned; } ;
struct rds_ib_mr {unsigned int sg_len; struct rds_ib_mr_pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rds_ib_teardown_mr (struct rds_ib_mr*) ; 
 int /*<<< orphan*/  atomic_sub (unsigned int,int /*<<< orphan*/ *) ; 

void rds_ib_teardown_mr(struct rds_ib_mr *ibmr)
{
	unsigned int pinned = ibmr->sg_len;

	__rds_ib_teardown_mr(ibmr);
	if (pinned) {
		struct rds_ib_mr_pool *pool = ibmr->pool;

		atomic_sub(pinned, &pool->free_pinned);
	}
}
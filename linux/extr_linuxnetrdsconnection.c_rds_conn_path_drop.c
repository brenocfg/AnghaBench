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
struct rds_conn_path {int /*<<< orphan*/  cp_down_w; int /*<<< orphan*/  cp_conn; int /*<<< orphan*/  cp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_CONN_ERROR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rds_destroy_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 

void rds_conn_path_drop(struct rds_conn_path *cp, bool destroy)
{
	atomic_set(&cp->cp_state, RDS_CONN_ERROR);

	rcu_read_lock();
	if (!destroy && rds_destroy_pending(cp->cp_conn)) {
		rcu_read_unlock();
		return;
	}
	queue_work(rds_wq, &cp->cp_down_w);
	rcu_read_unlock();
}
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
struct rds_conn_path {int /*<<< orphan*/  cp_conn_w; int /*<<< orphan*/  cp_flags; int /*<<< orphan*/  cp_conn; } ;

/* Variables and functions */
 scalar_t__ RDS_CONN_DOWN ; 
 int /*<<< orphan*/  RDS_RECONNECT_PENDING ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rds_conn_path_state (struct rds_conn_path*) ; 
 scalar_t__ rds_destroy_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_conn_path_connect_if_down(struct rds_conn_path *cp)
{
	rcu_read_lock();
	if (rds_destroy_pending(cp->cp_conn)) {
		rcu_read_unlock();
		return;
	}
	if (rds_conn_path_state(cp) == RDS_CONN_DOWN &&
	    !test_and_set_bit(RDS_RECONNECT_PENDING, &cp->cp_flags))
		queue_delayed_work(rds_wq, &cp->cp_conn_w, 0);
	rcu_read_unlock();
}
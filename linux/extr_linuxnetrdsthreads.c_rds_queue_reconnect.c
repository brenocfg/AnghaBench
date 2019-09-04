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
struct rds_connection {int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; TYPE_1__* c_trans; } ;
struct rds_conn_path {unsigned long cp_reconnect_jiffies; int /*<<< orphan*/  cp_conn_w; struct rds_connection* cp_conn; int /*<<< orphan*/  cp_flags; } ;
typedef  int /*<<< orphan*/  rand ;
struct TYPE_2__ {scalar_t__ t_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_RECONNECT_PENDING ; 
 scalar_t__ RDS_TRANS_TCP ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 unsigned long min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ rds_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_destroy_pending (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_sysctl_reconnect_max_jiffies ; 
 unsigned long rds_sysctl_reconnect_min_jiffies ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_queue_reconnect(struct rds_conn_path *cp)
{
	unsigned long rand;
	struct rds_connection *conn = cp->cp_conn;

	rdsdebug("conn %p for %pI6c to %pI6c reconnect jiffies %lu\n",
		 conn, &conn->c_laddr, &conn->c_faddr,
		 cp->cp_reconnect_jiffies);

	/* let peer with smaller addr initiate reconnect, to avoid duels */
	if (conn->c_trans->t_type == RDS_TRANS_TCP &&
	    rds_addr_cmp(&conn->c_laddr, &conn->c_faddr) >= 0)
		return;

	set_bit(RDS_RECONNECT_PENDING, &cp->cp_flags);
	if (cp->cp_reconnect_jiffies == 0) {
		cp->cp_reconnect_jiffies = rds_sysctl_reconnect_min_jiffies;
		rcu_read_lock();
		if (!rds_destroy_pending(cp->cp_conn))
			queue_delayed_work(rds_wq, &cp->cp_conn_w, 0);
		rcu_read_unlock();
		return;
	}

	get_random_bytes(&rand, sizeof(rand));
	rdsdebug("%lu delay %lu ceil conn %p for %pI6c -> %pI6c\n",
		 rand % cp->cp_reconnect_jiffies, cp->cp_reconnect_jiffies,
		 conn, &conn->c_laddr, &conn->c_faddr);
	rcu_read_lock();
	if (!rds_destroy_pending(cp->cp_conn))
		queue_delayed_work(rds_wq, &cp->cp_conn_w,
				   rand % cp->cp_reconnect_jiffies);
	rcu_read_unlock();

	cp->cp_reconnect_jiffies = min(cp->cp_reconnect_jiffies * 2,
					rds_sysctl_reconnect_max_jiffies);
}
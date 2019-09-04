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
struct rds_connection {struct rds_conn_path* c_path; int /*<<< orphan*/  c_hash_node; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; TYPE_1__* c_trans; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_retrans; } ;
struct TYPE_2__ {scalar_t__ t_mp_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int RDS_MPATH_WORKERS ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rds_conn_path*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rds_connection*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_cong_remove_conn (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_conn_count ; 
 int /*<<< orphan*/  rds_conn_lock ; 
 int /*<<< orphan*/  rds_conn_path_destroy (struct rds_conn_path*) ; 
 int /*<<< orphan*/  rds_conn_slab ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void rds_conn_destroy(struct rds_connection *conn)
{
	unsigned long flags;
	int i;
	struct rds_conn_path *cp;
	int npaths = (conn->c_trans->t_mp_capable ? RDS_MPATH_WORKERS : 1);

	rdsdebug("freeing conn %p for %pI4 -> "
		 "%pI4\n", conn, &conn->c_laddr,
		 &conn->c_faddr);

	/* Ensure conn will not be scheduled for reconnect */
	spin_lock_irq(&rds_conn_lock);
	hlist_del_init_rcu(&conn->c_hash_node);
	spin_unlock_irq(&rds_conn_lock);
	synchronize_rcu();

	/* shut the connection down */
	for (i = 0; i < npaths; i++) {
		cp = &conn->c_path[i];
		rds_conn_path_destroy(cp);
		BUG_ON(!list_empty(&cp->cp_retrans));
	}

	/*
	 * The congestion maps aren't freed up here.  They're
	 * freed by rds_cong_exit() after all the connections
	 * have been freed.
	 */
	rds_cong_remove_conn(conn);

	kfree(conn->c_path);
	kmem_cache_free(rds_conn_slab, conn);

	spin_lock_irqsave(&rds_conn_lock, flags);
	rds_conn_count--;
	spin_unlock_irqrestore(&rds_conn_lock, flags);
}
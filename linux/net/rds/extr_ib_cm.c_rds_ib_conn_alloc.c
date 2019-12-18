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
struct rds_ib_connection {int /*<<< orphan*/  ib_node; struct rds_connection* conn; int /*<<< orphan*/  i_recv_ring; int /*<<< orphan*/  i_send_ring; int /*<<< orphan*/  i_fastreg_wrs; int /*<<< orphan*/  i_signaled_sends; int /*<<< orphan*/  i_ack_lock; int /*<<< orphan*/  i_recv_mutex; int /*<<< orphan*/  i_recv_tasklet; int /*<<< orphan*/  i_send_tasklet; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDS_IB_DEFAULT_FR_WR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_nodev_conns ; 
 int /*<<< orphan*/  ib_nodev_conns_lock ; 
 int /*<<< orphan*/  kfree (struct rds_ib_connection*) ; 
 struct rds_ib_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int rds_ib_recv_alloc_caches (struct rds_ib_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_sysctl_max_recv_wr ; 
 int /*<<< orphan*/  rds_ib_sysctl_max_send_wr ; 
 int /*<<< orphan*/  rds_ib_tasklet_fn_recv ; 
 int /*<<< orphan*/  rds_ib_tasklet_fn_send ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,struct rds_ib_connection*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int rds_ib_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_ib_connection *ic;
	unsigned long flags;
	int ret;

	/* XXX too lazy? */
	ic = kzalloc(sizeof(struct rds_ib_connection), gfp);
	if (!ic)
		return -ENOMEM;

	ret = rds_ib_recv_alloc_caches(ic, gfp);
	if (ret) {
		kfree(ic);
		return ret;
	}

	INIT_LIST_HEAD(&ic->ib_node);
	tasklet_init(&ic->i_send_tasklet, rds_ib_tasklet_fn_send,
		     (unsigned long)ic);
	tasklet_init(&ic->i_recv_tasklet, rds_ib_tasklet_fn_recv,
		     (unsigned long)ic);
	mutex_init(&ic->i_recv_mutex);
#ifndef KERNEL_HAS_ATOMIC64
	spin_lock_init(&ic->i_ack_lock);
#endif
	atomic_set(&ic->i_signaled_sends, 0);
	atomic_set(&ic->i_fastreg_wrs, RDS_IB_DEFAULT_FR_WR);

	/*
	 * rds_ib_conn_shutdown() waits for these to be emptied so they
	 * must be initialized before it can be called.
	 */
	rds_ib_ring_init(&ic->i_send_ring, rds_ib_sysctl_max_send_wr);
	rds_ib_ring_init(&ic->i_recv_ring, rds_ib_sysctl_max_recv_wr);

	ic->conn = conn;
	conn->c_transport_data = ic;

	spin_lock_irqsave(&ib_nodev_conns_lock, flags);
	list_add_tail(&ic->ib_node, &ib_nodev_conns);
	spin_unlock_irqrestore(&ib_nodev_conns_lock, flags);


	rdsdebug("conn %p conn ic %p\n", conn, conn->c_transport_data);
	return 0;
}
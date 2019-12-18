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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct rds_sock {int /*<<< orphan*/  rs_transport; int /*<<< orphan*/  rs_item; int /*<<< orphan*/  rs_zcookie_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_clear_recv_queue (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_cong_remove_socket (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_notify_msg_zcopy_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_notify_queue_get (struct rds_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_rdma_drop_keys (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_remove_bound (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_send_drop_to (struct rds_sock*,int /*<<< orphan*/ *) ; 
 struct rds_sock* rds_sk_to_rs (struct sock*) ; 
 int /*<<< orphan*/  rds_sock_count ; 
 int /*<<< orphan*/  rds_sock_lock ; 
 int /*<<< orphan*/  rds_trans_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct rds_sock *rs;

	if (!sk)
		goto out;

	rs = rds_sk_to_rs(sk);

	sock_orphan(sk);
	/* Note - rds_clear_recv_queue grabs rs_recv_lock, so
	 * that ensures the recv path has completed messing
	 * with the socket. */
	rds_clear_recv_queue(rs);
	rds_cong_remove_socket(rs);

	rds_remove_bound(rs);

	rds_send_drop_to(rs, NULL);
	rds_rdma_drop_keys(rs);
	rds_notify_queue_get(rs, NULL);
	rds_notify_msg_zcopy_purge(&rs->rs_zcookie_queue);

	spin_lock_bh(&rds_sock_lock);
	list_del_init(&rs->rs_item);
	rds_sock_count--;
	spin_unlock_bh(&rds_sock_lock);

	rds_trans_put(rs->rs_transport);

	sock->sk = NULL;
	sock_put(sk);
out:
	return 0;
}
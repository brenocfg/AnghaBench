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
struct sock {void (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_callback_lock; struct rds_conn_path* sk_user_data; } ;
struct rds_tcp_connection {void (* t_orig_data_ready ) (struct sock*) ;} ;
struct rds_conn_path {int /*<<< orphan*/  cp_recv_w; int /*<<< orphan*/  cp_conn; struct rds_tcp_connection* cp_transport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rds_destroy_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_read_sock (struct rds_conn_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,struct sock*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_tcp_data_ready_calls ; 

void rds_tcp_data_ready(struct sock *sk)
{
	void (*ready)(struct sock *sk);
	struct rds_conn_path *cp;
	struct rds_tcp_connection *tc;

	rdsdebug("data ready sk %p\n", sk);

	read_lock_bh(&sk->sk_callback_lock);
	cp = sk->sk_user_data;
	if (!cp) { /* check for teardown race */
		ready = sk->sk_data_ready;
		goto out;
	}

	tc = cp->cp_transport_data;
	ready = tc->t_orig_data_ready;
	rds_tcp_stats_inc(s_tcp_data_ready_calls);

	if (rds_tcp_read_sock(cp, GFP_ATOMIC) == -ENOMEM) {
		rcu_read_lock();
		if (!rds_destroy_pending(cp->cp_conn))
			queue_delayed_work(rds_wq, &cp->cp_recv_w, 0);
		rcu_read_unlock();
	}
out:
	read_unlock_bh(&sk->sk_callback_lock);
	ready(sk);
}
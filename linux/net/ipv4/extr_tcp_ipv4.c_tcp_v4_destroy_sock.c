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
struct tcp_sock {int /*<<< orphan*/  fastopen_rsk; int /*<<< orphan*/ * md5sig_info; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_bind_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  kfree_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_sockets_allocated_dec (struct sock*) ; 
 int /*<<< orphan*/  skb_rbtree_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_cleanup_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  tcp_cleanup_ulp (struct sock*) ; 
 int /*<<< orphan*/  tcp_clear_md5_list (struct sock*) ; 
 int /*<<< orphan*/  tcp_clear_xmit_timers (struct sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_active_disable_ofo_check (struct sock*) ; 
 int /*<<< orphan*/  tcp_fastopen_destroy_cipher (struct sock*) ; 
 int /*<<< orphan*/  tcp_free_fastopen_req (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_saved_syn_free (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 
 int /*<<< orphan*/  trace_tcp_destroy_sock (struct sock*) ; 

void tcp_v4_destroy_sock(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	trace_tcp_destroy_sock(sk);

	tcp_clear_xmit_timers(sk);

	tcp_cleanup_congestion_control(sk);

	tcp_cleanup_ulp(sk);

	/* Cleanup up the write buffer. */
	tcp_write_queue_purge(sk);

	/* Check if we want to disable active TFO */
	tcp_fastopen_active_disable_ofo_check(sk);

	/* Cleans up our, hopefully empty, out_of_order_queue. */
	skb_rbtree_purge(&tp->out_of_order_queue);

#ifdef CONFIG_TCP_MD5SIG
	/* Clean up the MD5 key list, if any */
	if (tp->md5sig_info) {
		tcp_clear_md5_list(sk);
		kfree_rcu(rcu_dereference_protected(tp->md5sig_info, 1), rcu);
		tp->md5sig_info = NULL;
	}
#endif

	/* Clean up a referenced TCP bind bucket. */
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);

	BUG_ON(rcu_access_pointer(tp->fastopen_rsk));

	/* If socket is aborted during connect operation */
	tcp_free_fastopen_req(tp);
	tcp_fastopen_destroy_cipher(sk);
	tcp_saved_syn_free(tp);

	sk_sockets_allocated_dec(sk);
}
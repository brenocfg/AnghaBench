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
struct sock {int sk_state; int /*<<< orphan*/  sk_dst_cache; int /*<<< orphan*/  sk_receive_queue; } ;

/* Variables and functions */
 int PPPOX_DEAD ; 
 int /*<<< orphan*/  del_chan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppox_sk (struct sock*) ; 
 int /*<<< orphan*/  pppox_unbind_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pptp_sock_destruct(struct sock *sk)
{
	if (!(sk->sk_state & PPPOX_DEAD)) {
		del_chan(pppox_sk(sk));
		pppox_unbind_sock(sk);
	}
	skb_queue_purge(&sk->sk_receive_queue);
	dst_release(rcu_dereference_protected(sk->sk_dst_cache, 1));
}
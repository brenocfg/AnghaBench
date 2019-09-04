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
struct socket {struct sock* sk; } ;
struct sock {size_t sk_protocol; int /*<<< orphan*/  sk_write_queue; } ;
struct netlink_sock {int ngroups; int /*<<< orphan*/  rcu; int /*<<< orphan*/  module; scalar_t__ portid; scalar_t__ bound; int /*<<< orphan*/  wait; int /*<<< orphan*/  (* netlink_unbind ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  groups; } ;
struct netlink_notify {size_t protocol; scalar_t__ portid; int /*<<< orphan*/  net; } ;
struct listeners {int dummy; } ;
struct TYPE_2__ {scalar_t__ registered; scalar_t__ flags; int /*<<< orphan*/ * unbind; int /*<<< orphan*/ * bind; int /*<<< orphan*/ * module; int /*<<< orphan*/  listeners; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t NETLINK_GENERIC ; 
 int /*<<< orphan*/  NETLINK_URELEASE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct netlink_notify*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deferred_put_nlk_sk ; 
 int /*<<< orphan*/  genl_sk_destructing_cnt ; 
 int /*<<< orphan*/  genl_sk_destructing_waitq ; 
 int /*<<< orphan*/  kfree_rcu (struct listeners*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_chain ; 
 scalar_t__ netlink_is_kernel (struct sock*) ; 
 int /*<<< orphan*/  netlink_proto ; 
 int /*<<< orphan*/  netlink_remove (struct sock*) ; 
 int /*<<< orphan*/  netlink_table_grab () ; 
 int /*<<< orphan*/  netlink_table_ungrab () ; 
 struct listeners* nl_deref_protected (int /*<<< orphan*/ ) ; 
 TYPE_1__* nl_table ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_prot_inuse_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlink_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct netlink_sock *nlk;

	if (!sk)
		return 0;

	netlink_remove(sk);
	sock_orphan(sk);
	nlk = nlk_sk(sk);

	/*
	 * OK. Socket is unlinked, any packets that arrive now
	 * will be purged.
	 */

	/* must not acquire netlink_table_lock in any way again before unbind
	 * and notifying genetlink is done as otherwise it might deadlock
	 */
	if (nlk->netlink_unbind) {
		int i;

		for (i = 0; i < nlk->ngroups; i++)
			if (test_bit(i, nlk->groups))
				nlk->netlink_unbind(sock_net(sk), i + 1);
	}
	if (sk->sk_protocol == NETLINK_GENERIC &&
	    atomic_dec_return(&genl_sk_destructing_cnt) == 0)
		wake_up(&genl_sk_destructing_waitq);

	sock->sk = NULL;
	wake_up_interruptible_all(&nlk->wait);

	skb_queue_purge(&sk->sk_write_queue);

	if (nlk->portid && nlk->bound) {
		struct netlink_notify n = {
						.net = sock_net(sk),
						.protocol = sk->sk_protocol,
						.portid = nlk->portid,
					  };
		blocking_notifier_call_chain(&netlink_chain,
				NETLINK_URELEASE, &n);
	}

	module_put(nlk->module);

	if (netlink_is_kernel(sk)) {
		netlink_table_grab();
		BUG_ON(nl_table[sk->sk_protocol].registered == 0);
		if (--nl_table[sk->sk_protocol].registered == 0) {
			struct listeners *old;

			old = nl_deref_protected(nl_table[sk->sk_protocol].listeners);
			RCU_INIT_POINTER(nl_table[sk->sk_protocol].listeners, NULL);
			kfree_rcu(old, rcu);
			nl_table[sk->sk_protocol].module = NULL;
			nl_table[sk->sk_protocol].bind = NULL;
			nl_table[sk->sk_protocol].unbind = NULL;
			nl_table[sk->sk_protocol].flags = 0;
			nl_table[sk->sk_protocol].registered = 0;
		}
		netlink_table_ungrab();
	}

	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), &netlink_proto, -1);
	local_bh_enable();
	call_rcu(&nlk->rcu, deferred_put_nlk_sk);
	return 0;
}
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
struct sock {int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_receive_queue; } ;
struct netns_pfkey {int /*<<< orphan*/  socks_nr; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct netns_pfkey* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_net_id ; 
 int /*<<< orphan*/  pfkey_sk (struct sock*) ; 
 int /*<<< orphan*/  pfkey_terminate_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct sock*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 

__attribute__((used)) static void pfkey_sock_destruct(struct sock *sk)
{
	struct net *net = sock_net(sk);
	struct netns_pfkey *net_pfkey = net_generic(net, pfkey_net_id);

	pfkey_terminate_dump(pfkey_sk(sk));
	skb_queue_purge(&sk->sk_receive_queue);

	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_err("Attempt to release alive pfkey socket: %p\n", sk);
		return;
	}

	WARN_ON(atomic_read(&sk->sk_rmem_alloc));
	WARN_ON(refcount_read(&sk->sk_wmem_alloc));

	atomic_dec(&net_pfkey->socks_nr);
}
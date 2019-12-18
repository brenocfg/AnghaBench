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
struct udphdr {int dummy; } ;
struct udp_bearer {int /*<<< orphan*/  bearer; } ;
struct tipc_msg {int dummy; } ;
struct tipc_bearer {int /*<<< orphan*/  up; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ LINK_CONFIG ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 struct tipc_bearer* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct udp_bearer* rcu_dereference_sk_user_data (struct sock*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_rcv (int /*<<< orphan*/ ,struct sk_buff*,struct tipc_bearer*) ; 
 int tipc_udp_rcast_disc (struct tipc_bearer*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_udp_recv(struct sock *sk, struct sk_buff *skb)
{
	struct udp_bearer *ub;
	struct tipc_bearer *b;
	struct tipc_msg *hdr;
	int err;

	ub = rcu_dereference_sk_user_data(sk);
	if (!ub) {
		pr_err_ratelimited("Failed to get UDP bearer reference");
		goto out;
	}
	skb_pull(skb, sizeof(struct udphdr));
	hdr = buf_msg(skb);

	b = rcu_dereference(ub->bearer);
	if (!b)
		goto out;

	if (b && test_bit(0, &b->up)) {
		tipc_rcv(sock_net(sk), skb, b);
		return 0;
	}

	if (unlikely(msg_user(hdr) == LINK_CONFIG)) {
		err = tipc_udp_rcast_disc(b, skb);
		if (err)
			goto out;
	}

out:
	kfree_skb(skb);
	return 0;
}
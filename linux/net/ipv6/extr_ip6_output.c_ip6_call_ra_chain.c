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
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct ipv6_pinfo {scalar_t__ rtalert_isolate; } ;
struct ip6_ra_chain {int sel; struct sock* sk; struct ip6_ra_chain* next; } ;
struct TYPE_2__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_net (TYPE_1__*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct ip6_ra_chain* ip6_ra_chain ; 
 int /*<<< orphan*/  ip6_ra_lock ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawv6_rcv (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int ip6_call_ra_chain(struct sk_buff *skb, int sel)
{
	struct ip6_ra_chain *ra;
	struct sock *last = NULL;

	read_lock(&ip6_ra_lock);
	for (ra = ip6_ra_chain; ra; ra = ra->next) {
		struct sock *sk = ra->sk;
		if (sk && ra->sel == sel &&
		    (!sk->sk_bound_dev_if ||
		     sk->sk_bound_dev_if == skb->dev->ifindex)) {
			struct ipv6_pinfo *np = inet6_sk(sk);

			if (np && np->rtalert_isolate &&
			    !net_eq(sock_net(sk), dev_net(skb->dev))) {
				continue;
			}
			if (last) {
				struct sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);
				if (skb2)
					rawv6_rcv(last, skb2);
			}
			last = sk;
		}
	}

	if (last) {
		rawv6_rcv(last, skb);
		read_unlock(&ip6_ra_lock);
		return 1;
	}
	read_unlock(&ip6_ra_lock);
	return 0;
}
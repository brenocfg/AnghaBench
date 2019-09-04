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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {struct sock* sk; } ;
struct flowi6 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_oif; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_local_rxpmtu (struct sock*,struct flowi6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xfrm6_local_rxpmtu(struct sk_buff *skb, u32 mtu)
{
	struct flowi6 fl6;
	struct sock *sk = skb->sk;

	fl6.flowi6_oif = sk->sk_bound_dev_if;
	fl6.daddr = ipv6_hdr(skb)->daddr;

	ipv6_local_rxpmtu(sk, &fl6, mtu);
}
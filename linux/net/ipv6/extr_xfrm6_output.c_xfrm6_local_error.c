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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ encapsulation; struct sock* sk; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct flowi6 {int /*<<< orphan*/  daddr; int /*<<< orphan*/  fl6_dport; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 struct ipv6hdr* inner_ipv6_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_local_error (struct sock*,int /*<<< orphan*/ ,struct flowi6*,int /*<<< orphan*/ ) ; 

void xfrm6_local_error(struct sk_buff *skb, u32 mtu)
{
	struct flowi6 fl6;
	const struct ipv6hdr *hdr;
	struct sock *sk = skb->sk;

	hdr = skb->encapsulation ? inner_ipv6_hdr(skb) : ipv6_hdr(skb);
	fl6.fl6_dport = inet_sk(sk)->inet_dport;
	fl6.daddr = hdr->daddr;

	ipv6_local_error(sk, EMSGSIZE, &fl6, mtu);
}
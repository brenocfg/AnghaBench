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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {struct in6_addr daddr; struct in6_addr saddr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 int RAW_HTABLE_SIZE ; 
 struct sock* __raw_v6_lookup (struct net*,struct sock*,int,struct in6_addr const*,struct in6_addr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 TYPE_1__ raw_v6_hashinfo ; 
 int /*<<< orphan*/  rawv6_err (struct sock*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sock* sk_head (int /*<<< orphan*/ *) ; 
 struct sock* sk_next (struct sock*) ; 

void raw6_icmp_error(struct sk_buff *skb, int nexthdr,
		u8 type, u8 code, int inner_offset, __be32 info)
{
	struct sock *sk;
	int hash;
	const struct in6_addr *saddr, *daddr;
	struct net *net;

	hash = nexthdr & (RAW_HTABLE_SIZE - 1);

	read_lock(&raw_v6_hashinfo.lock);
	sk = sk_head(&raw_v6_hashinfo.ht[hash]);
	if (sk) {
		/* Note: ipv6_hdr(skb) != skb->data */
		const struct ipv6hdr *ip6h = (const struct ipv6hdr *)skb->data;
		saddr = &ip6h->saddr;
		daddr = &ip6h->daddr;
		net = dev_net(skb->dev);

		while ((sk = __raw_v6_lookup(net, sk, nexthdr, saddr, daddr,
					     inet6_iif(skb), inet6_iif(skb)))) {
			rawv6_err(sk, skb, NULL, type, code,
					inner_offset, info);
			sk = sk_next(sk);
		}
	}
	read_unlock(&raw_v6_hashinfo.lock);
}
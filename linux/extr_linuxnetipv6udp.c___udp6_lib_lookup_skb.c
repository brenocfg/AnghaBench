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
struct udp_table {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct sock* __udp6_lib_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct udp_table*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  inet6_sdif (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static struct sock *__udp6_lib_lookup_skb(struct sk_buff *skb,
					  __be16 sport, __be16 dport,
					  struct udp_table *udptable)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);

	return __udp6_lib_lookup(dev_net(skb->dev), &iph->saddr, sport,
				 &iph->daddr, dport, inet6_iif(skb),
				 inet6_sdif(skb), udptable, skb);
}
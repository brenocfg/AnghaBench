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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  mark; scalar_t__ data; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi6 {int flowi6_oif; int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_mark; } ;
struct dst_entry {int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IP6_REPLY_MARK (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ip6_rt_update_pmtu (struct dst_entry*,int /*<<< orphan*/ *,struct ipv6hdr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  ip6_flowinfo (struct ipv6hdr const*) ; 
 struct dst_entry* ip6_route_output (struct net*,int /*<<< orphan*/ *,struct flowi6*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void ip6_update_pmtu(struct sk_buff *skb, struct net *net, __be32 mtu,
		     int oif, u32 mark, kuid_t uid)
{
	const struct ipv6hdr *iph = (struct ipv6hdr *) skb->data;
	struct dst_entry *dst;
	struct flowi6 fl6 = {
		.flowi6_oif = oif,
		.flowi6_mark = mark ? mark : IP6_REPLY_MARK(net, skb->mark),
		.daddr = iph->daddr,
		.saddr = iph->saddr,
		.flowlabel = ip6_flowinfo(iph),
		.flowi6_uid = uid,
	};

	dst = ip6_route_output(net, NULL, &fl6);
	if (!dst->error)
		__ip6_rt_update_pmtu(dst, NULL, iph, ntohl(mtu));
	dst_release(dst);
}
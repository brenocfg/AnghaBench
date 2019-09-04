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
struct sk_buff {int dummy; } ;
struct rd_msg {int /*<<< orphan*/  dest; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct flowi6 {int flowi6_oif; int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  flowi6_iif; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl6 ;

/* Variables and functions */
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 scalar_t__ icmp6_hdr (struct sk_buff*) ; 
 struct dst_entry* ip6_route_redirect (struct net*,struct flowi6*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt6_do_redirect (struct dst_entry*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 

void ip6_redirect_no_header(struct sk_buff *skb, struct net *net, int oif,
			    u32 mark)
{
	const struct ipv6hdr *iph = ipv6_hdr(skb);
	const struct rd_msg *msg = (struct rd_msg *)icmp6_hdr(skb);
	struct dst_entry *dst;
	struct flowi6 fl6;

	memset(&fl6, 0, sizeof(fl6));
	fl6.flowi6_iif = LOOPBACK_IFINDEX;
	fl6.flowi6_oif = oif;
	fl6.flowi6_mark = mark;
	fl6.daddr = msg->dest;
	fl6.saddr = iph->daddr;
	fl6.flowi6_uid = sock_net_uid(net, NULL);

	dst = ip6_route_redirect(net, &fl6, skb, &iph->saddr);
	rt6_do_redirect(dst, NULL, skb);
	dst_release(dst);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {TYPE_2__* dev; } ;
struct net {int dummy; } ;
struct ipv6hdr {int /*<<< orphan*/  daddr; } ;
struct ila_net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct ila_map {TYPE_1__ xp; } ;
struct ila_addr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct net* dev_net (TYPE_2__*) ; 
 struct ila_addr* ila_a2i (int /*<<< orphan*/ *) ; 
 struct ila_map* ila_lookup_wildcards (struct ila_addr*,int /*<<< orphan*/ ,struct ila_net*) ; 
 int /*<<< orphan*/  ila_net_id ; 
 int /*<<< orphan*/  ila_update_ipv6_locator (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 struct ila_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ila_xlat_addr(struct sk_buff *skb, bool sir2ila)
{
	struct ila_map *ila;
	struct ipv6hdr *ip6h = ipv6_hdr(skb);
	struct net *net = dev_net(skb->dev);
	struct ila_net *ilan = net_generic(net, ila_net_id);
	struct ila_addr *iaddr = ila_a2i(&ip6h->daddr);

	/* Assumes skb contains a valid IPv6 header that is pulled */

	/* No check here that ILA type in the mapping matches what is in the
	 * address. We assume that whatever sender gaves us can be translated.
	 * The checksum mode however is relevant.
	 */

	rcu_read_lock();

	ila = ila_lookup_wildcards(iaddr, skb->dev->ifindex, ilan);
	if (ila)
		ila_update_ipv6_locator(skb, &ila->xp.ip, sir2ila);

	rcu_read_unlock();

	return 0;
}
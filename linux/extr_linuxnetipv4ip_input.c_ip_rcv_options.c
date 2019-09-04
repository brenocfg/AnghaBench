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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct iphdr {int ihl; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_options {int optlen; int /*<<< orphan*/  srr; } ;
struct in_device {int dummy; } ;
struct TYPE_2__ {struct ip_options opt; } ;

/* Variables and functions */
 scalar_t__ IN_DEV_LOG_MARTIANS (struct in_device*) ; 
 int /*<<< orphan*/  IN_DEV_SOURCE_ROUTE (struct in_device*) ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_INDISCARDS ; 
 int /*<<< orphan*/  IPSTATS_MIB_INHDRERRORS ; 
 int /*<<< orphan*/  __IP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct in_device* __in_dev_get_rcu (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_options_compile (int /*<<< orphan*/ ,struct ip_options*,struct sk_buff*) ; 
 scalar_t__ ip_options_rcv_srr (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ip_rcv_options(struct sk_buff *skb, struct net_device *dev)
{
	struct ip_options *opt;
	const struct iphdr *iph;

	/* It looks as overkill, because not all
	   IP options require packet mangling.
	   But it is the easiest for now, especially taking
	   into account that combination of IP options
	   and running sniffer is extremely rare condition.
					      --ANK (980813)
	*/
	if (skb_cow(skb, skb_headroom(skb))) {
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INDISCARDS);
		goto drop;
	}

	iph = ip_hdr(skb);
	opt = &(IPCB(skb)->opt);
	opt->optlen = iph->ihl*4 - sizeof(struct iphdr);

	if (ip_options_compile(dev_net(dev), opt, skb)) {
		__IP_INC_STATS(dev_net(dev), IPSTATS_MIB_INHDRERRORS);
		goto drop;
	}

	if (unlikely(opt->srr)) {
		struct in_device *in_dev = __in_dev_get_rcu(dev);

		if (in_dev) {
			if (!IN_DEV_SOURCE_ROUTE(in_dev)) {
				if (IN_DEV_LOG_MARTIANS(in_dev))
					net_info_ratelimited("source route option %pI4 -> %pI4\n",
							     &iph->saddr,
							     &iph->daddr);
				goto drop;
			}
		}

		if (ip_options_rcv_srr(skb, dev))
			goto drop;
	}

	return false;
drop:
	return true;
}
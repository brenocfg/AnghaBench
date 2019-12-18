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
struct xfrm_state {scalar_t__ if_id; } ;
struct TYPE_4__ {scalar_t__ if_id; } ;
struct xfrm_if {int /*<<< orphan*/  net; TYPE_2__ p; TYPE_1__* dev; } ;
struct sk_buff {unsigned int len; scalar_t__ protocol; int /*<<< orphan*/  sk; struct net_device* dev; int /*<<< orphan*/  ignore_df; } ;
struct pcpu_sw_netstats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct net_device_stats {int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  collisions; } ;
struct net_device {int /*<<< orphan*/  tstats; int /*<<< orphan*/  name; } ;
struct flowi {int dummy; } ;
struct dst_entry {struct net_device* dev; struct xfrm_state* xfrm; } ;
struct TYPE_3__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ICMPV6_PKT_TOOBIG ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 int IPV6_MIN_MTU ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int PTR_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dst_hold (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_link_failure (struct sk_buff*) ; 
 int dst_mtu (struct dst_entry*) ; 
 int dst_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ net_xmit_eval (int) ; 
 struct xfrm_if* netdev_priv (struct net_device*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int /*<<< orphan*/  skb_dst_update_pmtu (struct sk_buff*,int) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 struct dst_entry* xfrm_lookup_with_ifid (int /*<<< orphan*/ ,struct dst_entry*,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfrmi_scrub_packet (struct sk_buff*,int) ; 

__attribute__((used)) static int
xfrmi_xmit2(struct sk_buff *skb, struct net_device *dev, struct flowi *fl)
{
	struct xfrm_if *xi = netdev_priv(dev);
	struct net_device_stats *stats = &xi->dev->stats;
	struct dst_entry *dst = skb_dst(skb);
	unsigned int length = skb->len;
	struct net_device *tdev;
	struct xfrm_state *x;
	int err = -1;
	int mtu;

	if (!dst)
		goto tx_err_link_failure;

	dst_hold(dst);
	dst = xfrm_lookup_with_ifid(xi->net, dst, fl, NULL, 0, xi->p.if_id);
	if (IS_ERR(dst)) {
		err = PTR_ERR(dst);
		dst = NULL;
		goto tx_err_link_failure;
	}

	x = dst->xfrm;
	if (!x)
		goto tx_err_link_failure;

	if (x->if_id != xi->p.if_id)
		goto tx_err_link_failure;

	tdev = dst->dev;

	if (tdev == dev) {
		stats->collisions++;
		net_warn_ratelimited("%s: Local routing loop detected!\n",
				     dev->name);
		goto tx_err_dst_release;
	}

	mtu = dst_mtu(dst);
	if (!skb->ignore_df && skb->len > mtu) {
		skb_dst_update_pmtu(skb, mtu);

		if (skb->protocol == htons(ETH_P_IPV6)) {
			if (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		} else {
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				  htonl(mtu));
		}

		dst_release(dst);
		return -EMSGSIZE;
	}

	xfrmi_scrub_packet(skb, !net_eq(xi->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = tdev;

	err = dst_output(xi->net, skb->sk, skb);
	if (net_xmit_eval(err) == 0) {
		struct pcpu_sw_netstats *tstats = this_cpu_ptr(dev->tstats);

		u64_stats_update_begin(&tstats->syncp);
		tstats->tx_bytes += length;
		tstats->tx_packets++;
		u64_stats_update_end(&tstats->syncp);
	} else {
		stats->tx_errors++;
		stats->tx_aborted_errors++;
	}

	return 0;
tx_err_link_failure:
	stats->tx_carrier_errors++;
	dst_link_failure(skb);
tx_err_dst_release:
	dst_release(dst);
	return err;
}
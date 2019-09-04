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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_pcpu_stats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct vlan_ethhdr {scalar_t__ h_vlan_proto; } ;
struct vlan_dev_priv {scalar_t__ vlan_proto; int flags; TYPE_1__* vlan_pcpu_stats; int /*<<< orphan*/  real_dev; int /*<<< orphan*/  vlan_id; } ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct net_device {int dummy; } ;
typedef  int netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 int VLAN_FLAG_REORDER_HDR ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netpoll_tx_running (struct net_device*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct vlan_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_dev_get_egress_qos_mask (struct net_device*,int /*<<< orphan*/ ) ; 
 struct vlan_dev_priv* vlan_dev_priv (struct net_device*) ; 
 int vlan_netpoll_send_skb (struct vlan_dev_priv*,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t vlan_dev_hard_start_xmit(struct sk_buff *skb,
					    struct net_device *dev)
{
	struct vlan_dev_priv *vlan = vlan_dev_priv(dev);
	struct vlan_ethhdr *veth = (struct vlan_ethhdr *)(skb->data);
	unsigned int len;
	int ret;

	/* Handle non-VLAN frames if they are sent to us, for example by DHCP.
	 *
	 * NOTE: THIS ASSUMES DIX ETHERNET, SPECIFICALLY NOT SUPPORTING
	 * OTHER THINGS LIKE FDDI/TokenRing/802.3 SNAPs...
	 */
	if (veth->h_vlan_proto != vlan->vlan_proto ||
	    vlan->flags & VLAN_FLAG_REORDER_HDR) {
		u16 vlan_tci;
		vlan_tci = vlan->vlan_id;
		vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb->priority);
		__vlan_hwaccel_put_tag(skb, vlan->vlan_proto, vlan_tci);
	}

	skb->dev = vlan->real_dev;
	len = skb->len;
	if (unlikely(netpoll_tx_running(dev)))
		return vlan_netpoll_send_skb(vlan, skb);

	ret = dev_queue_xmit(skb);

	if (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) {
		struct vlan_pcpu_stats *stats;

		stats = this_cpu_ptr(vlan->vlan_pcpu_stats);
		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += len;
		u64_stats_update_end(&stats->syncp);
	} else {
		this_cpu_inc(vlan->vlan_pcpu_stats->tx_dropped);
	}

	return ret;
}
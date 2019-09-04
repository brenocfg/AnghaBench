#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  sin_family; TYPE_3__ sin_addr; } ;
union vxlan_addr {TYPE_4__ sin; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  tip ;
struct vxlan_fdb {int dummy; } ;
struct TYPE_7__ {int flags; } ;
struct vxlan_dev {TYPE_2__ cfg; } ;
struct sk_buff {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {int flags; scalar_t__ addr_len; TYPE_1__ stats; } ;
struct neighbour {int nud_state; int /*<<< orphan*/  ha; } ;
struct arphdr {scalar_t__ ar_hrd; scalar_t__ ar_pro; scalar_t__ ar_op; scalar_t__ ar_hln; int ar_pln; } ;
typedef  int /*<<< orphan*/  sip ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {int /*<<< orphan*/  remote_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ARPHRD_IEEE802 ; 
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  ARPOP_REQUEST ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int IFF_NOARP ; 
 int NETDEV_TX_OK ; 
 scalar_t__ NET_RX_DROP ; 
 int NUD_CONNECTED ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int VXLAN_F_L3MISS ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* arp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct arphdr* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  arp_hdr_len (struct net_device*) ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 TYPE_5__* first_remote_rcu (struct vxlan_fdb*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_loopback (int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct neighbour* neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ vxlan_addr_any (int /*<<< orphan*/ *) ; 
 struct vxlan_fdb* vxlan_find_mac (struct vxlan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_ip_miss (struct net_device*,union vxlan_addr*) ; 

__attribute__((used)) static int arp_reduce(struct net_device *dev, struct sk_buff *skb, __be32 vni)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct arphdr *parp;
	u8 *arpptr, *sha;
	__be32 sip, tip;
	struct neighbour *n;

	if (dev->flags & IFF_NOARP)
		goto out;

	if (!pskb_may_pull(skb, arp_hdr_len(dev))) {
		dev->stats.tx_dropped++;
		goto out;
	}
	parp = arp_hdr(skb);

	if ((parp->ar_hrd != htons(ARPHRD_ETHER) &&
	     parp->ar_hrd != htons(ARPHRD_IEEE802)) ||
	    parp->ar_pro != htons(ETH_P_IP) ||
	    parp->ar_op != htons(ARPOP_REQUEST) ||
	    parp->ar_hln != dev->addr_len ||
	    parp->ar_pln != 4)
		goto out;
	arpptr = (u8 *)parp + sizeof(struct arphdr);
	sha = arpptr;
	arpptr += dev->addr_len;	/* sha */
	memcpy(&sip, arpptr, sizeof(sip));
	arpptr += sizeof(sip);
	arpptr += dev->addr_len;	/* tha */
	memcpy(&tip, arpptr, sizeof(tip));

	if (ipv4_is_loopback(tip) ||
	    ipv4_is_multicast(tip))
		goto out;

	n = neigh_lookup(&arp_tbl, &tip, dev);

	if (n) {
		struct vxlan_fdb *f;
		struct sk_buff	*reply;

		if (!(n->nud_state & NUD_CONNECTED)) {
			neigh_release(n);
			goto out;
		}

		f = vxlan_find_mac(vxlan, n->ha, vni);
		if (f && vxlan_addr_any(&(first_remote_rcu(f)->remote_ip))) {
			/* bridge-local neighbor */
			neigh_release(n);
			goto out;
		}

		reply = arp_create(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip, sha,
				n->ha, sha);

		neigh_release(n);

		if (reply == NULL)
			goto out;

		skb_reset_mac_header(reply);
		__skb_pull(reply, skb_network_offset(reply));
		reply->ip_summed = CHECKSUM_UNNECESSARY;
		reply->pkt_type = PACKET_HOST;

		if (netif_rx_ni(reply) == NET_RX_DROP)
			dev->stats.rx_dropped++;
	} else if (vxlan->cfg.flags & VXLAN_F_L3MISS) {
		union vxlan_addr ipa = {
			.sin.sin_addr.s_addr = tip,
			.sin.sin_family = AF_INET,
		};

		vxlan_ip_miss(dev, &ipa);
	}
out:
	consume_skb(skb);
	return NETDEV_TX_OK;
}
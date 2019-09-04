#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vlan_ethhdr {int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {int len; void* data; } ;
struct TYPE_6__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_5__ {int /*<<< orphan*/  dft_eps_id; } ;
struct nic {int vlan_id; TYPE_3__ stats; TYPE_2__ pdn_table; TYPE_1__* phy_dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int (* send_sdu_func ) (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nic*,int,int) ;int /*<<< orphan*/  priv_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMEDIUMTYPE ; 
 int ENODEV ; 
 int ENOSPC ; 
 int ETH_HLEN ; 
 int NIC_TYPE_ARP ; 
 int NIC_TYPE_F_DHCP ; 
 int NIC_TYPE_F_VLAN ; 
 int NIC_TYPE_ICMPV6 ; 
 int NIC_TYPE_MASK ; 
 int TX_NO_BUFFER ; 
 int TX_NO_DEV ; 
 int TX_NO_SPC ; 
 int VLAN_ETH_HLEN ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ gdm_lte_emulate_arp (struct sk_buff*,int) ; 
 scalar_t__ gdm_lte_emulate_ndp (struct sk_buff*,int) ; 
 int gdm_lte_tx_nic_type (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int stub1 (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nic*,int,int) ; 
 int /*<<< orphan*/  tx_complete ; 

__attribute__((used)) static netdev_tx_t gdm_lte_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct nic *nic = netdev_priv(dev);
	u32 nic_type;
	void *data_buf;
	int data_len;
	int idx;
	int ret = 0;

	nic_type = gdm_lte_tx_nic_type(dev, skb);
	if (nic_type == 0) {
		netdev_err(dev, "tx - invalid nic_type\n");
		return -EMEDIUMTYPE;
	}

	if (nic_type & NIC_TYPE_ARP) {
		if (gdm_lte_emulate_arp(skb, nic_type) == 0) {
			dev_kfree_skb(skb);
			return 0;
		}
	}

	if (nic_type & NIC_TYPE_ICMPV6) {
		if (gdm_lte_emulate_ndp(skb, nic_type) == 0) {
			dev_kfree_skb(skb);
			return 0;
		}
	}

	/*
	 * Need byte shift (that is, remove VLAN tag) if there is one
	 * For the case of ARP, this breaks the offset as vlan_ethhdr+4
	 * is treated as ethhdr	However, it shouldn't be a problem as
	 * the response starts from arp_hdr and ethhdr is created by this
	 * driver based on the NIC mac
	 */
	if (nic_type & NIC_TYPE_F_VLAN) {
		struct vlan_ethhdr *vlan_eth = (struct vlan_ethhdr *)skb->data;

		nic->vlan_id = ntohs(vlan_eth->h_vlan_TCI) & VLAN_VID_MASK;
		data_buf = skb->data + (VLAN_ETH_HLEN - ETH_HLEN);
		data_len = skb->len - (VLAN_ETH_HLEN - ETH_HLEN);
	} else {
		nic->vlan_id = 0;
		data_buf = skb->data;
		data_len = skb->len;
	}

	/* If it is a ICMPV6 packet, clear all the other bits :
	 * for backward compatibility with the firmware
	 */
	if (nic_type & NIC_TYPE_ICMPV6)
		nic_type = NIC_TYPE_ICMPV6;

	/* If it is not a dhcp packet, clear all the flag bits :
	 * original NIC, otherwise the special flag (IPVX | DHCP)
	 */
	if (!(nic_type & NIC_TYPE_F_DHCP))
		nic_type &= NIC_TYPE_MASK;

	ret = sscanf(dev->name, "lte%d", &idx);
	if (ret != 1) {
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	ret = nic->phy_dev->send_sdu_func(nic->phy_dev->priv_dev,
					  data_buf, data_len,
					  nic->pdn_table.dft_eps_id, 0,
					  tx_complete, nic, idx,
					  nic_type);

	if (ret == TX_NO_BUFFER || ret == TX_NO_SPC) {
		netif_stop_queue(dev);
		if (ret == TX_NO_BUFFER)
			ret = 0;
		else
			ret = -ENOSPC;
	} else if (ret == TX_NO_DEV) {
		ret = -ENODEV;
	}

	/* Updates tx stats */
	if (ret) {
		nic->stats.tx_dropped++;
	} else {
		nic->stats.tx_packets++;
		nic->stats.tx_bytes += data_len;
	}
	dev_kfree_skb(skb);

	return 0;
}
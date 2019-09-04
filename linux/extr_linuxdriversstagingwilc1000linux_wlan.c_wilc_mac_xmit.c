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
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct wilc_vif {size_t idx; TYPE_1__ netstats; struct wilc* wilc; } ;
struct wilc {TYPE_2__** vif; } ;
struct tx_complete_data {scalar_t__ size; scalar_t__ buff; int /*<<< orphan*/  bssid; struct sk_buff* skb; } ;
struct sk_buff {scalar_t__ data; scalar_t__ len; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct iphdr {int dummy; } ;
struct ethhdr {scalar_t__ h_proto; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  ndev; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int FLOW_CONTROL_UPPER_THRESHOLD ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct tx_complete_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_wlan_tx_complete ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int wilc_wlan_txq_add_net_pkt (struct net_device*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

netdev_tx_t wilc_mac_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct wilc_vif *vif = netdev_priv(ndev);
	struct wilc *wilc = vif->wilc;
	struct tx_complete_data *tx_data = NULL;
	int queue_count;
	char *udp_buf;
	struct iphdr *ih;
	struct ethhdr *eth_h;

	if (skb->dev != ndev) {
		netdev_err(ndev, "Packet not destined to this device\n");
		return 0;
	}

	tx_data = kmalloc(sizeof(*tx_data), GFP_ATOMIC);
	if (!tx_data) {
		dev_kfree_skb(skb);
		netif_wake_queue(ndev);
		return 0;
	}

	tx_data->buff = skb->data;
	tx_data->size = skb->len;
	tx_data->skb  = skb;

	eth_h = (struct ethhdr *)(skb->data);
	if (eth_h->h_proto == cpu_to_be16(0x8e88))
		netdev_dbg(ndev, "EAPOL transmitted\n");

	ih = (struct iphdr *)(skb->data + sizeof(struct ethhdr));

	udp_buf = (char *)ih + sizeof(struct iphdr);
	if ((udp_buf[1] == 68 && udp_buf[3] == 67) ||
	    (udp_buf[1] == 67 && udp_buf[3] == 68))
		netdev_dbg(ndev, "DHCP Message transmitted, type:%x %x %x\n",
			   udp_buf[248], udp_buf[249], udp_buf[250]);

	vif->netstats.tx_packets++;
	vif->netstats.tx_bytes += tx_data->size;
	tx_data->bssid = wilc->vif[vif->idx]->bssid;
	queue_count = wilc_wlan_txq_add_net_pkt(ndev, (void *)tx_data,
						tx_data->buff, tx_data->size,
						linux_wlan_tx_complete);

	if (queue_count > FLOW_CONTROL_UPPER_THRESHOLD) {
		netif_stop_queue(wilc->vif[0]->ndev);
		netif_stop_queue(wilc->vif[1]->ndev);
	}

	return 0;
}
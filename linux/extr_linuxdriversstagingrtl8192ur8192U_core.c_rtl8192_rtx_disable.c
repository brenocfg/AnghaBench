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
typedef  int u8 ;
struct sk_buff {scalar_t__ cb; } ;
struct rtl8192_rx_info {int /*<<< orphan*/  urb; } ;
struct r8192_priv {int /*<<< orphan*/  skb_queue; int /*<<< orphan*/  rx_queue; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDR ; 
 int CR_RE ; 
 int CR_TE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8192_rtx_disable(struct net_device *dev)
{
	u8 cmd;
	struct r8192_priv *priv = ieee80211_priv(dev);
	struct sk_buff *skb;
	struct rtl8192_rx_info *info;

	read_nic_byte(dev, CMDR, &cmd);
	write_nic_byte(dev, CMDR, cmd & ~(CR_TE | CR_RE));
	force_pci_posting(dev);
	mdelay(10);

	while ((skb = __skb_dequeue(&priv->rx_queue))) {
		info = (struct rtl8192_rx_info *)skb->cb;
		if (!info->urb)
			continue;

		usb_kill_urb(info->urb);
		kfree_skb(skb);
	}

	if (skb_queue_len(&priv->skb_queue))
		netdev_warn(dev, "skb_queue not empty\n");

	skb_queue_purge(&priv->skb_queue);
}
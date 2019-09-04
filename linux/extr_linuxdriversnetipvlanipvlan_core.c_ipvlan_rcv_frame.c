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
struct sk_buff {unsigned int len; struct net_device* dev; int /*<<< orphan*/  pkt_type; } ;
struct net_device {int flags; } ;
struct ipvl_dev {struct net_device* dev; } ;
struct ipvl_addr {struct ipvl_dev* master; } ;
typedef  int rx_handler_result_t ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_UP ; 
 scalar_t__ NET_RX_SUCCESS ; 
 int /*<<< orphan*/  PACKET_HOST ; 
 int RX_HANDLER_ANOTHER ; 
 int RX_HANDLER_CONSUMED ; 
 scalar_t__ dev_forward_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipvlan_count_rx (struct ipvl_dev*,unsigned int,int,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipvlan_rcv_frame(struct ipvl_addr *addr, struct sk_buff **pskb,
			    bool local)
{
	struct ipvl_dev *ipvlan = addr->master;
	struct net_device *dev = ipvlan->dev;
	unsigned int len;
	rx_handler_result_t ret = RX_HANDLER_CONSUMED;
	bool success = false;
	struct sk_buff *skb = *pskb;

	len = skb->len + ETH_HLEN;
	/* Only packets exchanged between two local slaves need to have
	 * device-up check as well as skb-share check.
	 */
	if (local) {
		if (unlikely(!(dev->flags & IFF_UP))) {
			kfree_skb(skb);
			goto out;
		}

		skb = skb_share_check(skb, GFP_ATOMIC);
		if (!skb)
			goto out;

		*pskb = skb;
	}

	if (local) {
		skb->pkt_type = PACKET_HOST;
		if (dev_forward_skb(ipvlan->dev, skb) == NET_RX_SUCCESS)
			success = true;
	} else {
		skb->dev = dev;
		ret = RX_HANDLER_ANOTHER;
		success = true;
	}

out:
	ipvlan_count_rx(ipvlan, len, success, false);
	return ret;
}
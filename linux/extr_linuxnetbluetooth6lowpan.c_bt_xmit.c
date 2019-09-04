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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int netdev_tx_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_2__ {scalar_t__ chan; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_1__* lowpan_cb (struct sk_buff*) ; 
 int send_mcast_pkt (struct sk_buff*,struct net_device*) ; 
 int send_pkt (scalar_t__,struct sk_buff*,struct net_device*) ; 
 int setup_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bt_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	int err = 0;
	bdaddr_t addr;
	u8 addr_type;

	/* We must take a copy of the skb before we modify/replace the ipv6
	 * header as the header could be used elsewhere
	 */
	skb = skb_unshare(skb, GFP_ATOMIC);
	if (!skb)
		return NET_XMIT_DROP;

	/* Return values from setup_header()
	 *  <0 - error, packet is dropped
	 *   0 - this is a multicast packet
	 *   1 - this is unicast packet
	 */
	err = setup_header(skb, netdev, &addr, &addr_type);
	if (err < 0) {
		kfree_skb(skb);
		return NET_XMIT_DROP;
	}

	if (err) {
		if (lowpan_cb(skb)->chan) {
			BT_DBG("xmit %s to %pMR type %d IP %pI6c chan %p",
			       netdev->name, &addr, addr_type,
			       &lowpan_cb(skb)->addr, lowpan_cb(skb)->chan);
			err = send_pkt(lowpan_cb(skb)->chan, skb, netdev);
		} else {
			err = -ENOENT;
		}
	} else {
		/* We need to send the packet to every device behind this
		 * interface.
		 */
		err = send_mcast_pkt(skb, netdev);
	}

	dev_kfree_skb(skb);

	if (err)
		BT_DBG("ERROR: xmit failed (%d)", err);

	return err < 0 ? NET_XMIT_DROP : err;
}
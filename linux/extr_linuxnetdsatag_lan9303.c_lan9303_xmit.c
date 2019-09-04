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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int ETH_P_8021Q ; 
 scalar_t__ LAN9303_TAG_LEN ; 
 int LAN9303_TAG_TX_STP_OVERRIDE ; 
 int LAN9303_TAG_TX_USE_ALR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int htons (int) ; 
 scalar_t__ lan9303_xmit_use_arl (struct dsa_port*,scalar_t__) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *lan9303_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	u16 *lan9303_tag;

	/* insert a special VLAN tag between the MAC addresses
	 * and the current ethertype field.
	 */
	if (skb_cow_head(skb, LAN9303_TAG_LEN) < 0) {
		dev_dbg(&dev->dev,
			"Cannot make room for the special tag. Dropping packet\n");
		return NULL;
	}

	/* provide 'LAN9303_TAG_LEN' bytes additional space */
	skb_push(skb, LAN9303_TAG_LEN);

	/* make room between MACs and Ether-Type */
	memmove(skb->data, skb->data + LAN9303_TAG_LEN, 2 * ETH_ALEN);

	lan9303_tag = (u16 *)(skb->data + 2 * ETH_ALEN);
	lan9303_tag[0] = htons(ETH_P_8021Q);
	lan9303_tag[1] = lan9303_xmit_use_arl(dp, skb->data) ?
				LAN9303_TAG_TX_USE_ALR :
				dp->index | LAN9303_TAG_TX_STP_OVERRIDE;
	lan9303_tag[1] = htons(lan9303_tag[1]);

	return skb;
}
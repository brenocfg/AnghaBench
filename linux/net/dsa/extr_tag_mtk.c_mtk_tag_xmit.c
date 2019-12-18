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
struct sk_buff {int* data; } ;
struct net_device {int dummy; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MTK_HDR_LEN ; 
 int MTK_HDR_XMIT_DP_BIT_MASK ; 
 int MTK_HDR_XMIT_TAGGED_TPID_8100 ; 
 int MTK_HDR_XMIT_UNTAGGED ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_vlan_tagged (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *mtk_tag_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	u8 *mtk_tag;
	bool is_vlan_skb = true;

	/* Build the special tag after the MAC Source Address. If VLAN header
	 * is present, it's required that VLAN header and special tag is
	 * being combined. Only in this way we can allow the switch can parse
	 * the both special and VLAN tag at the same time and then look up VLAN
	 * table with VID.
	 */
	if (!skb_vlan_tagged(skb)) {
		if (skb_cow_head(skb, MTK_HDR_LEN) < 0)
			return NULL;

		skb_push(skb, MTK_HDR_LEN);
		memmove(skb->data, skb->data + MTK_HDR_LEN, 2 * ETH_ALEN);
		is_vlan_skb = false;
	}

	mtk_tag = skb->data + 2 * ETH_ALEN;

	/* Mark tag attribute on special tag insertion to notify hardware
	 * whether that's a combined special tag with 802.1Q header.
	 */
	mtk_tag[0] = is_vlan_skb ? MTK_HDR_XMIT_TAGGED_TPID_8100 :
		     MTK_HDR_XMIT_UNTAGGED;
	mtk_tag[1] = (1 << dp->index) & MTK_HDR_XMIT_DP_BIT_MASK;

	/* Tag control information is kept for 802.1Q */
	if (!is_vlan_skb) {
		mtk_tag[2] = 0;
		mtk_tag[3] = 0;
	}

	return skb;
}
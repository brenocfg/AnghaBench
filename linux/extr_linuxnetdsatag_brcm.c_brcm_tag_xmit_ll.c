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
typedef  int u16 ;
struct sk_buff {int* data; } ;
struct net_device {int dummy; } ;
struct dsa_port {int index; } ;

/* Variables and functions */
 int BRCM_IG_DSTMAP1_MASK ; 
 int BRCM_IG_DSTMAP2_MASK ; 
 int BRCM_IG_TC_MASK ; 
 int BRCM_IG_TC_SHIFT ; 
 int BRCM_OPCODE_SHIFT ; 
 int BRCM_TAG_LEN ; 
 int /*<<< orphan*/  BRCM_TAG_SET_PORT_QUEUE (int,int) ; 
 int ETH_ZLEN ; 
 scalar_t__ __skb_put_padto (struct sk_buff*,int,int) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  memmove (int*,int*,unsigned int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *brcm_tag_xmit_ll(struct sk_buff *skb,
					struct net_device *dev,
					unsigned int offset)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	u16 queue = skb_get_queue_mapping(skb);
	u8 *brcm_tag;

	if (skb_cow_head(skb, BRCM_TAG_LEN) < 0)
		return NULL;

	/* The Ethernet switch we are interfaced with needs packets to be at
	 * least 64 bytes (including FCS) otherwise they will be discarded when
	 * they enter the switch port logic. When Broadcom tags are enabled, we
	 * need to make sure that packets are at least 68 bytes
	 * (including FCS and tag) because the length verification is done after
	 * the Broadcom tag is stripped off the ingress packet.
	 *
	 * Let dsa_slave_xmit() free the SKB
	 */
	if (__skb_put_padto(skb, ETH_ZLEN + BRCM_TAG_LEN, false))
		return NULL;

	skb_push(skb, BRCM_TAG_LEN);

	if (offset)
		memmove(skb->data, skb->data + BRCM_TAG_LEN, offset);

	brcm_tag = skb->data + offset;

	/* Set the ingress opcode, traffic class, tag enforcment is
	 * deprecated
	 */
	brcm_tag[0] = (1 << BRCM_OPCODE_SHIFT) |
		       ((queue & BRCM_IG_TC_MASK) << BRCM_IG_TC_SHIFT);
	brcm_tag[1] = 0;
	brcm_tag[2] = 0;
	if (dp->index == 8)
		brcm_tag[2] = BRCM_IG_DSTMAP2_MASK;
	brcm_tag[3] = (1 << dp->index) & BRCM_IG_DSTMAP1_MASK;

	/* Now tell the master network device about the desired output queue
	 * as well
	 */
	skb_set_queue_mapping(skb, BRCM_TAG_SET_PORT_QUEUE(dp->index, queue));

	return skb;
}
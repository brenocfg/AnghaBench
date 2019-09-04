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
struct sk_buff {unsigned int data; int /*<<< orphan*/  dev; } ;
struct packet_type {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BRCM_EG_PID_MASK ; 
 int BRCM_EG_RC_RSVD ; 
 int BRCM_OPCODE_MASK ; 
 int BRCM_OPCODE_SHIFT ; 
 int /*<<< orphan*/  BRCM_TAG_LEN ; 
 int /*<<< orphan*/  dsa_master_find_slave (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull_rcsum (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *brcm_tag_rcv_ll(struct sk_buff *skb,
				       struct net_device *dev,
				       struct packet_type *pt,
				       unsigned int offset)
{
	int source_port;
	u8 *brcm_tag;

	if (unlikely(!pskb_may_pull(skb, BRCM_TAG_LEN)))
		return NULL;

	brcm_tag = skb->data - offset;

	/* The opcode should never be different than 0b000 */
	if (unlikely((brcm_tag[0] >> BRCM_OPCODE_SHIFT) & BRCM_OPCODE_MASK))
		return NULL;

	/* We should never see a reserved reason code without knowing how to
	 * handle it
	 */
	if (unlikely(brcm_tag[2] & BRCM_EG_RC_RSVD))
		return NULL;

	/* Locate which port this is coming from */
	source_port = brcm_tag[3] & BRCM_EG_PID_MASK;

	skb->dev = dsa_master_find_slave(dev, 0, source_port);
	if (!skb->dev)
		return NULL;

	/* Remove Broadcom tag and update checksum */
	skb_pull_rcsum(skb, BRCM_TAG_LEN);

	return skb;
}
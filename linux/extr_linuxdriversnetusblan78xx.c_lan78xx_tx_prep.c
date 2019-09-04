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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct lan78xx_net {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int TX_CMD_A_FCS_ ; 
 int TX_CMD_A_IPE_ ; 
 int TX_CMD_A_IVTG_ ; 
 int TX_CMD_A_LEN_MASK_ ; 
 int TX_CMD_A_LSO_ ; 
 int TX_CMD_A_TPE_ ; 
 int TX_CMD_B_MSS_MASK_ ; 
 int /*<<< orphan*/  TX_CMD_B_MSS_MIN_ ; 
 int TX_CMD_B_MSS_SHIFT_ ; 
 int TX_CMD_B_VTAG_MASK_ ; 
 int /*<<< orphan*/  TX_OVERHEAD ; 
 int /*<<< orphan*/  cpu_to_le32s (int*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ lan78xx_linearize (struct sk_buff*) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *lan78xx_tx_prep(struct lan78xx_net *dev,
				       struct sk_buff *skb, gfp_t flags)
{
	u32 tx_cmd_a, tx_cmd_b;

	if (skb_cow_head(skb, TX_OVERHEAD)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	if (lan78xx_linearize(skb) < 0)
		return NULL;

	tx_cmd_a = (u32)(skb->len & TX_CMD_A_LEN_MASK_) | TX_CMD_A_FCS_;

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		tx_cmd_a |= TX_CMD_A_IPE_ | TX_CMD_A_TPE_;

	tx_cmd_b = 0;
	if (skb_is_gso(skb)) {
		u16 mss = max(skb_shinfo(skb)->gso_size, TX_CMD_B_MSS_MIN_);

		tx_cmd_b = (mss << TX_CMD_B_MSS_SHIFT_) & TX_CMD_B_MSS_MASK_;

		tx_cmd_a |= TX_CMD_A_LSO_;
	}

	if (skb_vlan_tag_present(skb)) {
		tx_cmd_a |= TX_CMD_A_IVTG_;
		tx_cmd_b |= skb_vlan_tag_get(skb) & TX_CMD_B_VTAG_MASK_;
	}

	skb_push(skb, 4);
	cpu_to_le32s(&tx_cmd_b);
	memcpy(skb->data, &tx_cmd_b, 4);

	skb_push(skb, 4);
	cpu_to_le32s(&tx_cmd_a);
	memcpy(skb->data, &tx_cmd_a, 4);

	return skb;
}
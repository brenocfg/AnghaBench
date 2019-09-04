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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  tpd ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int produce_idx; } ;
struct emac_tx_queue {int produce_shift; int produce_mask; scalar_t__ produce_reg; TYPE_1__ tpd; } ;
struct emac_tpd {int dummy; } ;
struct emac_adapter {scalar_t__ base; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_VLAN_TO_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TPD_CVLAN_TAG_SET (struct emac_tpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPD_INSTC_SET (struct emac_tpd*,int) ; 
 int /*<<< orphan*/  TPD_TYP_SET (struct emac_tpd*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  emac_reg_update32 (scalar_t__,int,int) ; 
 scalar_t__ emac_tpd_num_free_descs (struct emac_tx_queue*) ; 
 scalar_t__ emac_tso_csum (struct emac_adapter*,struct emac_tx_queue*,struct sk_buff*,struct emac_tpd*) ; 
 int /*<<< orphan*/  emac_tx_fill_tpd (struct emac_adapter*,struct emac_tx_queue*,struct sk_buff*,struct emac_tpd*) ; 
 int /*<<< orphan*/  memset (struct emac_tpd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

int emac_mac_tx_buf_send(struct emac_adapter *adpt, struct emac_tx_queue *tx_q,
			 struct sk_buff *skb)
{
	struct emac_tpd tpd;
	u32 prod_idx;

	memset(&tpd, 0, sizeof(tpd));

	if (emac_tso_csum(adpt, tx_q, skb, &tpd) != 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (skb_vlan_tag_present(skb)) {
		u16 tag;

		EMAC_VLAN_TO_TAG(skb_vlan_tag_get(skb), tag);
		TPD_CVLAN_TAG_SET(&tpd, tag);
		TPD_INSTC_SET(&tpd, 1);
	}

	if (skb_network_offset(skb) != ETH_HLEN)
		TPD_TYP_SET(&tpd, 1);

	emac_tx_fill_tpd(adpt, tx_q, skb, &tpd);

	netdev_sent_queue(adpt->netdev, skb->len);

	/* Make sure the are enough free descriptors to hold one
	 * maximum-sized SKB.  We need one desc for each fragment,
	 * one for the checksum (emac_tso_csum), one for TSO, and
	 * and one for the SKB header.
	 */
	if (emac_tpd_num_free_descs(tx_q) < (MAX_SKB_FRAGS + 3))
		netif_stop_queue(adpt->netdev);

	/* update produce idx */
	prod_idx = (tx_q->tpd.produce_idx << tx_q->produce_shift) &
		    tx_q->produce_mask;
	emac_reg_update32(adpt->base + tx_q->produce_reg,
			  tx_q->produce_mask, prod_idx);

	return NETDEV_TX_OK;
}
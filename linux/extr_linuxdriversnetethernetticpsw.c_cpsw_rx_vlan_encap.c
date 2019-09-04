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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  dev; } ;
struct cpsw_priv {size_t emac_port; struct cpsw_common* cpsw; } ;
struct TYPE_3__ {scalar_t__ dual_emac; } ;
struct cpsw_common {TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {int port_vlan; } ;

/* Variables and functions */
 int CPSW_RX_VLAN_ENCAP_HDR_PKT_PRIO_TAG ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PKT_RESERV ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_MSK ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_SHIFT ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PKT_VLAN_TAG ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PRIO_MSK ; 
 int CPSW_RX_VLAN_ENCAP_HDR_PRIO_SHIFT ; 
 scalar_t__ CPSW_RX_VLAN_ENCAP_HDR_SIZE ; 
 int CPSW_RX_VLAN_ENCAP_HDR_VID_SHIFT ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ VLAN_HLEN ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 struct cpsw_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void cpsw_rx_vlan_encap(struct sk_buff *skb)
{
	struct cpsw_priv *priv = netdev_priv(skb->dev);
	struct cpsw_common *cpsw = priv->cpsw;
	u32 rx_vlan_encap_hdr = *((u32 *)skb->data);
	u16 vtag, vid, prio, pkt_type;

	/* Remove VLAN header encapsulation word */
	skb_pull(skb, CPSW_RX_VLAN_ENCAP_HDR_SIZE);

	pkt_type = (rx_vlan_encap_hdr >>
		    CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_SHIFT) &
		    CPSW_RX_VLAN_ENCAP_HDR_PKT_TYPE_MSK;
	/* Ignore unknown & Priority-tagged packets*/
	if (pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_RESERV ||
	    pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_PRIO_TAG)
		return;

	vid = (rx_vlan_encap_hdr >>
	       CPSW_RX_VLAN_ENCAP_HDR_VID_SHIFT) &
	       VLAN_VID_MASK;
	/* Ignore vid 0 and pass packet as is */
	if (!vid)
		return;
	/* Ignore default vlans in dual mac mode */
	if (cpsw->data.dual_emac &&
	    vid == cpsw->slaves[priv->emac_port].port_vlan)
		return;

	prio = (rx_vlan_encap_hdr >>
		CPSW_RX_VLAN_ENCAP_HDR_PRIO_SHIFT) &
		CPSW_RX_VLAN_ENCAP_HDR_PRIO_MSK;

	vtag = (prio << VLAN_PRIO_SHIFT) | vid;
	__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vtag);

	/* strip vlan tag for VLAN-tagged packet */
	if (pkt_type == CPSW_RX_VLAN_ENCAP_HDR_PKT_VLAN_TAG) {
		memmove(skb->data + VLAN_HLEN, skb->data, 2 * ETH_ALEN);
		skb_pull(skb, VLAN_HLEN);
	}
}
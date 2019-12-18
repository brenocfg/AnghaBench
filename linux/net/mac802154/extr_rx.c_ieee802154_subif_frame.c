#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wpan_dev {int /*<<< orphan*/  extended_addr; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  pan_id; } ;
struct sk_buff {scalar_t__ len; TYPE_3__* dev; void* pkt_type; } ;
struct ieee802154_sub_if_data {TYPE_3__* dev; int /*<<< orphan*/  sec; struct wpan_dev wpan_dev; } ;
struct ieee802154_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_5__ {int mode; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  pan_id; int /*<<< orphan*/  extended_addr; } ;
struct TYPE_8__ {int type; TYPE_1__ dest; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_7__ {int name; TYPE_2__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_ADDR_BROADCAST ; 
#define  IEEE802154_ADDR_LONG 134 
#define  IEEE802154_ADDR_NONE 133 
#define  IEEE802154_ADDR_SHORT 132 
#define  IEEE802154_FC_TYPE_ACK 131 
#define  IEEE802154_FC_TYPE_BEACON 130 
#define  IEEE802154_FC_TYPE_DATA 129 
#define  IEEE802154_FC_TYPE_MAC_CMD 128 
 int /*<<< orphan*/  IEEE802154_PANID_BROADCAST ; 
 int NET_RX_DROP ; 
 void* PACKET_BROADCAST ; 
 void* PACKET_HOST ; 
 void* PACKET_OTHERHOST ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int ieee802154_deliver_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int mac802154_llsec_decrypt (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_4__* mac_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int) ; 

__attribute__((used)) static int
ieee802154_subif_frame(struct ieee802154_sub_if_data *sdata,
		       struct sk_buff *skb, const struct ieee802154_hdr *hdr)
{
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;
	__le16 span, sshort;
	int rc;

	pr_debug("getting packet via slave interface %s\n", sdata->dev->name);

	span = wpan_dev->pan_id;
	sshort = wpan_dev->short_addr;

	switch (mac_cb(skb)->dest.mode) {
	case IEEE802154_ADDR_NONE:
		if (mac_cb(skb)->dest.mode != IEEE802154_ADDR_NONE)
			/* FIXME: check if we are PAN coordinator */
			skb->pkt_type = PACKET_OTHERHOST;
		else
			/* ACK comes with both addresses empty */
			skb->pkt_type = PACKET_HOST;
		break;
	case IEEE802154_ADDR_LONG:
		if (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_le16(IEEE802154_PANID_BROADCAST))
			skb->pkt_type = PACKET_OTHERHOST;
		else if (mac_cb(skb)->dest.extended_addr == wpan_dev->extended_addr)
			skb->pkt_type = PACKET_HOST;
		else
			skb->pkt_type = PACKET_OTHERHOST;
		break;
	case IEEE802154_ADDR_SHORT:
		if (mac_cb(skb)->dest.pan_id != span &&
		    mac_cb(skb)->dest.pan_id != cpu_to_le16(IEEE802154_PANID_BROADCAST))
			skb->pkt_type = PACKET_OTHERHOST;
		else if (mac_cb(skb)->dest.short_addr == sshort)
			skb->pkt_type = PACKET_HOST;
		else if (mac_cb(skb)->dest.short_addr ==
			  cpu_to_le16(IEEE802154_ADDR_BROADCAST))
			skb->pkt_type = PACKET_BROADCAST;
		else
			skb->pkt_type = PACKET_OTHERHOST;
		break;
	default:
		pr_debug("invalid dest mode\n");
		goto fail;
	}

	skb->dev = sdata->dev;

	/* TODO this should be moved after netif_receive_skb call, otherwise
	 * wireshark will show a mac header with security fields and the
	 * payload is already decrypted.
	 */
	rc = mac802154_llsec_decrypt(&sdata->sec, skb);
	if (rc) {
		pr_debug("decryption failed: %i\n", rc);
		goto fail;
	}

	sdata->dev->stats.rx_packets++;
	sdata->dev->stats.rx_bytes += skb->len;

	switch (mac_cb(skb)->type) {
	case IEEE802154_FC_TYPE_BEACON:
	case IEEE802154_FC_TYPE_ACK:
	case IEEE802154_FC_TYPE_MAC_CMD:
		goto fail;

	case IEEE802154_FC_TYPE_DATA:
		return ieee802154_deliver_skb(skb);
	default:
		pr_warn_ratelimited("ieee802154: bad frame received "
				    "(type = %d)\n", mac_cb(skb)->type);
		goto fail;
	}

fail:
	kfree_skb(skb);
	return NET_RX_DROP;
}
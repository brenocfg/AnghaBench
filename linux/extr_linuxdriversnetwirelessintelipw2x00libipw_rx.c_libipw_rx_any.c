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
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct libipw_rx_stats {int dummy; } ;
struct libipw_hdr_4addr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; } ;
struct libipw_hdr_3addr {int dummy; } ;
struct libipw_device {int iw_mode; TYPE_2__* dev; int /*<<< orphan*/  bssid; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_4__ {int flags; TYPE_1__ stats; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_TODS ; 
 int IEEE80211_FCTL_VERS ; 
#define  IEEE80211_FTYPE_CTL 132 
#define  IEEE80211_FTYPE_DATA 131 
#define  IEEE80211_FTYPE_MGMT 130 
 int IFF_PROMISC ; 
#define  IW_MODE_ADHOC 129 
#define  IW_MODE_INFRA 128 
 int IW_MODE_MONITOR ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libipw_rx (struct libipw_device*,struct sk_buff*,struct libipw_rx_stats*) ; 
 int /*<<< orphan*/  libipw_rx_mgt (struct libipw_device*,struct libipw_hdr_4addr*,struct libipw_rx_stats*) ; 

void libipw_rx_any(struct libipw_device *ieee,
		     struct sk_buff *skb, struct libipw_rx_stats *stats)
{
	struct libipw_hdr_4addr *hdr;
	int is_packet_for_us;
	u16 fc;

	if (ieee->iw_mode == IW_MODE_MONITOR) {
		if (!libipw_rx(ieee, skb, stats))
			dev_kfree_skb_irq(skb);
		return;
	}

	if (skb->len < sizeof(struct ieee80211_hdr))
		goto drop_free;

	hdr = (struct libipw_hdr_4addr *)skb->data;
	fc = le16_to_cpu(hdr->frame_ctl);

	if ((fc & IEEE80211_FCTL_VERS) != 0)
		goto drop_free;

	switch (fc & IEEE80211_FCTL_FTYPE) {
	case IEEE80211_FTYPE_MGMT:
		if (skb->len < sizeof(struct libipw_hdr_3addr))
			goto drop_free;
		libipw_rx_mgt(ieee, hdr, stats);
		dev_kfree_skb_irq(skb);
		return;
	case IEEE80211_FTYPE_DATA:
		break;
	case IEEE80211_FTYPE_CTL:
		return;
	default:
		return;
	}

	is_packet_for_us = 0;
	switch (ieee->iw_mode) {
	case IW_MODE_ADHOC:
		/* our BSS and not from/to DS */
		if (ether_addr_equal(hdr->addr3, ieee->bssid))
		if ((fc & (IEEE80211_FCTL_TODS+IEEE80211_FCTL_FROMDS)) == 0) {
			/* promisc: get all */
			if (ieee->dev->flags & IFF_PROMISC)
				is_packet_for_us = 1;
			/* to us */
			else if (ether_addr_equal(hdr->addr1, ieee->dev->dev_addr))
				is_packet_for_us = 1;
			/* mcast */
			else if (is_multicast_ether_addr(hdr->addr1))
				is_packet_for_us = 1;
		}
		break;
	case IW_MODE_INFRA:
		/* our BSS (== from our AP) and from DS */
		if (ether_addr_equal(hdr->addr2, ieee->bssid))
		if ((fc & (IEEE80211_FCTL_TODS+IEEE80211_FCTL_FROMDS)) == IEEE80211_FCTL_FROMDS) {
			/* promisc: get all */
			if (ieee->dev->flags & IFF_PROMISC)
				is_packet_for_us = 1;
			/* to us */
			else if (ether_addr_equal(hdr->addr1, ieee->dev->dev_addr))
				is_packet_for_us = 1;
			/* mcast */
			else if (is_multicast_ether_addr(hdr->addr1)) {
				/* not our own packet bcasted from AP */
				if (!ether_addr_equal(hdr->addr3, ieee->dev->dev_addr))
					is_packet_for_us = 1;
			}
		}
		break;
	default:
		/* ? */
		break;
	}

	if (is_packet_for_us)
		if (!libipw_rx(ieee, skb, stats))
			dev_kfree_skb_irq(skb);
	return;

drop_free:
	dev_kfree_skb_irq(skb);
	ieee->dev->stats.rx_dropped++;
}
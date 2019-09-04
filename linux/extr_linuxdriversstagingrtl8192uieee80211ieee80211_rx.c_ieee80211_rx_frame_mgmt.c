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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct rtl_80211_hdr_4addr {int dummy; } ;
struct rtl_80211_hdr_3addr {int /*<<< orphan*/  addr1; } ;
struct ieee80211_rx_stats {int /*<<< orphan*/  len; } ;
struct ieee80211_device {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_frame_softmac (struct ieee80211_device*,struct sk_buff*,struct ieee80211_rx_stats*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_mgt (struct ieee80211_device*,struct rtl_80211_hdr_4addr*,struct ieee80211_rx_stats*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ieee80211_rx_frame_mgmt(struct ieee80211_device *ieee, struct sk_buff *skb,
			struct ieee80211_rx_stats *rx_stats, u16 type,
			u16 stype)
{
	/* On the struct stats definition there is written that
	 * this is not mandatory.... but seems that the probe
	 * response parser uses it
	 */
	struct rtl_80211_hdr_3addr *hdr = (struct rtl_80211_hdr_3addr *)skb->data;

	rx_stats->len = skb->len;
	ieee80211_rx_mgt(ieee,(struct rtl_80211_hdr_4addr *)skb->data,rx_stats);
	/* if ((ieee->state == IEEE80211_LINKED) && (memcmp(hdr->addr3, ieee->current_network.bssid, ETH_ALEN))) */
	if ((memcmp(hdr->addr1, ieee->dev->dev_addr, ETH_ALEN)))/* use ADDR1 to perform address matching for Management frames */
	{
		dev_kfree_skb_any(skb);
		return 0;
	}

	ieee80211_rx_frame_softmac(ieee, skb, rx_stats, type, stype);

	dev_kfree_skb_any(skb);

	return 0;

	#ifdef NOT_YET
	if (ieee->iw_mode == IW_MODE_MASTER) {
		printk(KERN_DEBUG "%s: Master mode not yet supported.\n",
		       ieee->dev->name);
		return 0;
/*
  hostap_update_sta_ps(ieee, (struct hostap_ieee80211_hdr_4addr *)
  skb->data);*/
	}

	if (ieee->hostapd && type == IEEE80211_TYPE_MGMT) {
		if (stype == WLAN_FC_STYPE_BEACON &&
		    ieee->iw_mode == IW_MODE_MASTER) {
			struct sk_buff *skb2;
			/* Process beacon frames also in kernel driver to
			 * update STA(AP) table statistics */
			skb2 = skb_clone(skb, GFP_ATOMIC);
			if (skb2)
				hostap_rx(skb2->dev, skb2, rx_stats);
		}

		/* send management frames to the user space daemon for
		 * processing */
		ieee->apdevstats.rx_packets++;
		ieee->apdevstats.rx_bytes += skb->len;
		prism2_rx_80211(ieee->apdev, skb, rx_stats, PRISM2_RX_MGMT);
		return 0;
	}

	    if (ieee->iw_mode == IW_MODE_MASTER) {
		if (type != WLAN_FC_TYPE_MGMT && type != WLAN_FC_TYPE_CTRL) {
			printk(KERN_DEBUG "%s: unknown management frame "
			       "(type=0x%02x, stype=0x%02x) dropped\n",
			       skb->dev->name, type, stype);
			return -1;
		}

		hostap_rx(skb->dev, skb, rx_stats);
		return 0;
	}

	printk(KERN_DEBUG "%s: hostap_rx_frame_mgmt: management frame "
	       "received in non-Host AP mode\n", skb->dev->name);
	return -1;
	#endif
}
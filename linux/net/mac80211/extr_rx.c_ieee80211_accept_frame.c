#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_11__ {int /*<<< orphan*/ * remote_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  use_4addr; } ;
struct TYPE_12__ {TYPE_5__ wds; TYPE_2__ ibss; TYPE_1__ mgd; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/ * addr; } ;
struct ieee80211_sub_if_data {TYPE_6__ u; TYPE_4__ vif; TYPE_3__* dev; } ;
struct ieee80211_rx_status {int rate_idx; int /*<<< orphan*/  encoding; } ;
struct ieee80211_rx_data {int /*<<< orphan*/  sta; struct sk_buff* skb; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct TYPE_9__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
#define  NL80211_IFTYPE_ADHOC 136 
#define  NL80211_IFTYPE_AP 135 
#define  NL80211_IFTYPE_AP_VLAN 134 
#define  NL80211_IFTYPE_MESH_POINT 133 
#define  NL80211_IFTYPE_NAN 132 
#define  NL80211_IFTYPE_OCB 131 
#define  NL80211_IFTYPE_P2P_DEVICE 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_WDS 128 
 int /*<<< orphan*/  RX_ENC_LEGACY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_bssid_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_get_bssid (struct ieee80211_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_has_tods (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ibss_rx_no_sta (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_action (int /*<<< orphan*/ ) ; 
 int ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_public_action (struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_robust_mgmt_frame (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_ocb_rx_no_sta (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_accept_frame(struct ieee80211_rx_data *rx)
{
	struct ieee80211_sub_if_data *sdata = rx->sdata;
	struct sk_buff *skb = rx->skb;
	struct ieee80211_hdr *hdr = (void *)skb->data;
	struct ieee80211_rx_status *status = IEEE80211_SKB_RXCB(skb);
	u8 *bssid = ieee80211_get_bssid(hdr, skb->len, sdata->vif.type);
	bool multicast = is_multicast_ether_addr(hdr->addr1);

	switch (sdata->vif.type) {
	case NL80211_IFTYPE_STATION:
		if (!bssid && !sdata->u.mgd.use_4addr)
			return false;
		if (ieee80211_is_robust_mgmt_frame(skb) && !rx->sta)
			return false;
		if (multicast)
			return true;
		return ether_addr_equal(sdata->vif.addr, hdr->addr1);
	case NL80211_IFTYPE_ADHOC:
		if (!bssid)
			return false;
		if (ether_addr_equal(sdata->vif.addr, hdr->addr2) ||
		    ether_addr_equal(sdata->u.ibss.bssid, hdr->addr2))
			return false;
		if (ieee80211_is_beacon(hdr->frame_control))
			return true;
		if (!ieee80211_bssid_match(bssid, sdata->u.ibss.bssid))
			return false;
		if (!multicast &&
		    !ether_addr_equal(sdata->vif.addr, hdr->addr1))
			return false;
		if (!rx->sta) {
			int rate_idx;
			if (status->encoding != RX_ENC_LEGACY)
				rate_idx = 0; /* TODO: HT/VHT rates */
			else
				rate_idx = status->rate_idx;
			ieee80211_ibss_rx_no_sta(sdata, bssid, hdr->addr2,
						 BIT(rate_idx));
		}
		return true;
	case NL80211_IFTYPE_OCB:
		if (!bssid)
			return false;
		if (!ieee80211_is_data_present(hdr->frame_control))
			return false;
		if (!is_broadcast_ether_addr(bssid))
			return false;
		if (!multicast &&
		    !ether_addr_equal(sdata->dev->dev_addr, hdr->addr1))
			return false;
		if (!rx->sta) {
			int rate_idx;
			if (status->encoding != RX_ENC_LEGACY)
				rate_idx = 0; /* TODO: HT rates */
			else
				rate_idx = status->rate_idx;
			ieee80211_ocb_rx_no_sta(sdata, bssid, hdr->addr2,
						BIT(rate_idx));
		}
		return true;
	case NL80211_IFTYPE_MESH_POINT:
		if (ether_addr_equal(sdata->vif.addr, hdr->addr2))
			return false;
		if (multicast)
			return true;
		return ether_addr_equal(sdata->vif.addr, hdr->addr1);
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_AP:
		if (!bssid)
			return ether_addr_equal(sdata->vif.addr, hdr->addr1);

		if (!ieee80211_bssid_match(bssid, sdata->vif.addr)) {
			/*
			 * Accept public action frames even when the
			 * BSSID doesn't match, this is used for P2P
			 * and location updates. Note that mac80211
			 * itself never looks at these frames.
			 */
			if (!multicast &&
			    !ether_addr_equal(sdata->vif.addr, hdr->addr1))
				return false;
			if (ieee80211_is_public_action(hdr, skb->len))
				return true;
			return ieee80211_is_beacon(hdr->frame_control);
		}

		if (!ieee80211_has_tods(hdr->frame_control)) {
			/* ignore data frames to TDLS-peers */
			if (ieee80211_is_data(hdr->frame_control))
				return false;
			/* ignore action frames to TDLS-peers */
			if (ieee80211_is_action(hdr->frame_control) &&
			    !is_broadcast_ether_addr(bssid) &&
			    !ether_addr_equal(bssid, hdr->addr1))
				return false;
		}

		/*
		 * 802.11-2016 Table 9-26 says that for data frames, A1 must be
		 * the BSSID - we've checked that already but may have accepted
		 * the wildcard (ff:ff:ff:ff:ff:ff).
		 *
		 * It also says:
		 *	The BSSID of the Data frame is determined as follows:
		 *	a) If the STA is contained within an AP or is associated
		 *	   with an AP, the BSSID is the address currently in use
		 *	   by the STA contained in the AP.
		 *
		 * So we should not accept data frames with an address that's
		 * multicast.
		 *
		 * Accepting it also opens a security problem because stations
		 * could encrypt it with the GTK and inject traffic that way.
		 */
		if (ieee80211_is_data(hdr->frame_control) && multicast)
			return false;

		return true;
	case NL80211_IFTYPE_WDS:
		if (bssid || !ieee80211_is_data(hdr->frame_control))
			return false;
		return ether_addr_equal(sdata->u.wds.remote_addr, hdr->addr2);
	case NL80211_IFTYPE_P2P_DEVICE:
		return ieee80211_is_public_action(hdr, skb->len) ||
		       ieee80211_is_probe_req(hdr->frame_control) ||
		       ieee80211_is_probe_resp(hdr->frame_control) ||
		       ieee80211_is_beacon(hdr->frame_control);
	case NL80211_IFTYPE_NAN:
		/* Currently no frames on NAN interface are allowed */
		return false;
	default:
		break;
	}

	WARN_ON_ONCE(1);
	return false;
}
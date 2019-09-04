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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct p54_common {int mode; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_sta {int aid; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MAX_TIM_LEN ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int IEEE80211_TX_CTL_CLEAR_PS_FILT ; 
 int IEEE80211_TX_CTL_INJECTED ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_CTL_SEND_AFTER_DTIM ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 
 int P54_HDR_FLAG_DATA_OUT_NOCANCEL ; 
 int P54_HDR_FLAG_DATA_OUT_PROMISC ; 
 int P54_HDR_FLAG_DATA_OUT_SEQNR ; 
 int P54_HDR_FLAG_DATA_OUT_TIMESTAMP ; 
 scalar_t__ P54_QUEUE_BEACON ; 
 scalar_t__ P54_QUEUE_CAB ; 
 scalar_t__ P54_QUEUE_DATA ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p54_tx_80211_header(struct p54_common *priv, struct sk_buff *skb,
				struct ieee80211_tx_info *info,
				struct ieee80211_sta *sta,
				u8 *queue, u32 *extra_len, u16 *flags, u16 *aid,
				bool *burst_possible)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;

	if (ieee80211_is_data_qos(hdr->frame_control))
		*burst_possible = true;
	else
		*burst_possible = false;

	if (!(info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ))
		*flags |= P54_HDR_FLAG_DATA_OUT_SEQNR;

	if (info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER)
		*flags |= P54_HDR_FLAG_DATA_OUT_NOCANCEL;

	if (info->flags & IEEE80211_TX_CTL_CLEAR_PS_FILT)
		*flags |= P54_HDR_FLAG_DATA_OUT_NOCANCEL;

	*queue = skb_get_queue_mapping(skb) + P54_QUEUE_DATA;

	switch (priv->mode) {
	case NL80211_IFTYPE_MONITOR:
		/*
		 * We have to set P54_HDR_FLAG_DATA_OUT_PROMISC for
		 * every frame in promiscuous/monitor mode.
		 * see STSW45x0C LMAC API - page 12.
		 */
		*aid = 0;
		*flags |= P54_HDR_FLAG_DATA_OUT_PROMISC;
		break;
	case NL80211_IFTYPE_STATION:
		*aid = 1;
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_MESH_POINT:
		if (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) {
			*aid = 0;
			*queue = P54_QUEUE_CAB;
			return;
		}

		if (unlikely(ieee80211_is_mgmt(hdr->frame_control))) {
			if (ieee80211_is_probe_resp(hdr->frame_control)) {
				*aid = 0;
				*flags |= P54_HDR_FLAG_DATA_OUT_TIMESTAMP |
					  P54_HDR_FLAG_DATA_OUT_NOCANCEL;
				return;
			} else if (ieee80211_is_beacon(hdr->frame_control)) {
				*aid = 0;

				if (info->flags & IEEE80211_TX_CTL_INJECTED) {
					/*
					 * Injecting beacons on top of a AP is
					 * not a good idea... nevertheless,
					 * it should be doable.
					 */

					return;
				}

				*flags |= P54_HDR_FLAG_DATA_OUT_TIMESTAMP;
				*queue = P54_QUEUE_BEACON;
				*extra_len = IEEE80211_MAX_TIM_LEN;
				return;
			}
		}

		if (sta)
			*aid = sta->aid;
		break;
	}
}
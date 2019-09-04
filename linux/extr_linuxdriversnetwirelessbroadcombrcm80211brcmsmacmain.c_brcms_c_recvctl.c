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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_rx_status {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct d11rxhdr {int dummy; } ;
struct brcms_c_info {TYPE_1__* pub; TYPE_2__* hw; } ;
typedef  int /*<<< orphan*/  rx_status ;
struct TYPE_4__ {scalar_t__ suspended_fifos; } ;
struct TYPE_3__ {int /*<<< orphan*/  ieee_hw; } ;

/* Variables and functions */
 int D11_PHY_HDR_LEN ; 
 int FCS_LEN ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  brcms_b_mute (TYPE_2__*,int) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_irqsafe (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prep_mac80211_status (struct brcms_c_info*,struct d11rxhdr*,struct sk_buff*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void
brcms_c_recvctl(struct brcms_c_info *wlc, struct d11rxhdr *rxh,
		struct sk_buff *p)
{
	int len_mpdu;
	struct ieee80211_rx_status rx_status;
	struct ieee80211_hdr *hdr;

	memset(&rx_status, 0, sizeof(rx_status));
	prep_mac80211_status(wlc, rxh, p, &rx_status);

	/* mac header+body length, exclude CRC and plcp header */
	len_mpdu = p->len - D11_PHY_HDR_LEN - FCS_LEN;
	skb_pull(p, D11_PHY_HDR_LEN);
	__skb_trim(p, len_mpdu);

	/* unmute transmit */
	if (wlc->hw->suspended_fifos) {
		hdr = (struct ieee80211_hdr *)p->data;
		if (ieee80211_is_beacon(hdr->frame_control))
			brcms_b_mute(wlc->hw, false);
	}

	memcpy(IEEE80211_SKB_RXCB(p), &rx_status, sizeof(rx_status));
	ieee80211_rx_irqsafe(wlc->pub->ieee_hw, p);
}
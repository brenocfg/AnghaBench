#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {int /*<<< orphan*/  retry_count; } ;
struct wl1251 {struct sk_buff** tx_frames; int /*<<< orphan*/  hw; TYPE_3__ stats; } ;
struct tx_result {size_t id; int /*<<< orphan*/  status; int /*<<< orphan*/  rate; int /*<<< orphan*/  ack_failures; } ;
struct tx_double_buffer_desc {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_10__ {TYPE_4__* hw_key; } ;
struct TYPE_7__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_5__ control; TYPE_2__ status; } ;
struct TYPE_9__ {scalar_t__ cipher; } ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_INJECTED ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  TX_SUCCESS ; 
 int WL1251_TKIP_IV_SPACE ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,size_t,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_error (char*,size_t) ; 
 int /*<<< orphan*/  wl1251_tx_parse_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl1251_tx_packet_cb(struct wl1251 *wl,
				struct tx_result *result)
{
	struct ieee80211_tx_info *info;
	struct sk_buff *skb;
	int hdrlen;
	u8 *frame;

	skb = wl->tx_frames[result->id];
	if (skb == NULL) {
		wl1251_error("SKB for packet %d is NULL", result->id);
		return;
	}

	info = IEEE80211_SKB_CB(skb);

	if (!(info->flags & IEEE80211_TX_CTL_NO_ACK) &&
	    !(info->flags & IEEE80211_TX_CTL_INJECTED) &&
	    (result->status == TX_SUCCESS))
		info->flags |= IEEE80211_TX_STAT_ACK;

	info->status.rates[0].count = result->ack_failures + 1;
	wl->stats.retry_count += result->ack_failures;

	/*
	 * We have to remove our private TX header before pushing
	 * the skb back to mac80211.
	 */
	frame = skb_pull(skb, sizeof(struct tx_double_buffer_desc));
	if (info->control.hw_key &&
	    info->control.hw_key->cipher == WLAN_CIPHER_SUITE_TKIP) {
		hdrlen = ieee80211_get_hdrlen_from_skb(skb);
		memmove(frame + WL1251_TKIP_IV_SPACE, frame, hdrlen);
		skb_pull(skb, WL1251_TKIP_IV_SPACE);
	}

	wl1251_debug(DEBUG_TX, "tx status id %u skb 0x%p failures %u rate 0x%x"
		     " status 0x%x (%s)",
		     result->id, skb, result->ack_failures, result->rate,
		     result->status, wl1251_tx_parse_status(result->status));


	ieee80211_tx_status(wl->hw, skb);

	wl->tx_frames[result->id] = NULL;
}
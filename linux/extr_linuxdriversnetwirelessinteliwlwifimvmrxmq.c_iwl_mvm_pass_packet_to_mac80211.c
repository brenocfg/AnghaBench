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
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int flag; } ;
struct ieee80211_radiotap_he_mu {int dummy; } ;
struct ieee80211_radiotap_he {int dummy; } ;

/* Variables and functions */
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int RX_FLAG_RADIOTAP_HE ; 
 int RX_FLAG_RADIOTAP_HE_MU ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ieee80211_rx_napi (int /*<<< orphan*/ ,struct ieee80211_sta*,struct sk_buff*,struct napi_struct*) ; 
 scalar_t__ iwl_mvm_check_pn (struct iwl_mvm*,struct sk_buff*,int,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void iwl_mvm_pass_packet_to_mac80211(struct iwl_mvm *mvm,
					    struct napi_struct *napi,
					    struct sk_buff *skb, int queue,
					    struct ieee80211_sta *sta)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);

	if (iwl_mvm_check_pn(mvm, skb, queue, sta)) {
		kfree_skb(skb);
	} else {
		unsigned int radiotap_len = 0;

		if (rx_status->flag & RX_FLAG_RADIOTAP_HE)
			radiotap_len += sizeof(struct ieee80211_radiotap_he);
		if (rx_status->flag & RX_FLAG_RADIOTAP_HE_MU)
			radiotap_len += sizeof(struct ieee80211_radiotap_he_mu);
		__skb_push(skb, radiotap_len);
		ieee80211_rx_napi(mvm->hw, sta, skb, napi);
	}
}
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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct iwl_stored_beacon_notif {int band; int /*<<< orphan*/  data; int /*<<< orphan*/  channel; int /*<<< orphan*/  system_time; int /*<<< orphan*/  tsf; int /*<<< orphan*/  byte_count; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  band; int /*<<< orphan*/  freq; void* device_timestamp; int /*<<< orphan*/  flag; int /*<<< orphan*/  mactime; } ;
typedef  int /*<<< orphan*/  rx_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RX_FLAG_MACTIME_PLCP_START ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_BAND_24 ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_napi (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct ieee80211_rx_status*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

void iwl_mvm_rx_stored_beacon_notif(struct iwl_mvm *mvm,
				    struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_stored_beacon_notif *sb = (void *)pkt->data;
	struct ieee80211_rx_status rx_status;
	struct sk_buff *skb;
	u32 size = le32_to_cpu(sb->byte_count);

	if (size == 0)
		return;

	skb = alloc_skb(size, GFP_ATOMIC);
	if (!skb) {
		IWL_ERR(mvm, "alloc_skb failed\n");
		return;
	}

	/* update rx_status according to the notification's metadata */
	memset(&rx_status, 0, sizeof(rx_status));
	rx_status.mactime = le64_to_cpu(sb->tsf);
	/* TSF as indicated by the firmware  is at INA time */
	rx_status.flag |= RX_FLAG_MACTIME_PLCP_START;
	rx_status.device_timestamp = le32_to_cpu(sb->system_time);
	rx_status.band =
		(sb->band & cpu_to_le16(RX_RES_PHY_FLAGS_BAND_24)) ?
				NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	rx_status.freq =
		ieee80211_channel_to_frequency(le16_to_cpu(sb->channel),
					       rx_status.band);

	/* copy the data */
	skb_put_data(skb, sb->data, size);
	memcpy(IEEE80211_SKB_RXCB(skb), &rx_status, sizeof(rx_status));

	/* pass it as regular rx to mac80211 */
	ieee80211_rx_napi(mvm->hw, NULL, skb, NULL);
}
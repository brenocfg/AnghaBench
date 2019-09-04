#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  unsigned int u16 ;
struct rate_info {size_t mcs; int /*<<< orphan*/  legacy; int /*<<< orphan*/  flags; int /*<<< orphan*/  nss; int /*<<< orphan*/  bw; } ;
struct ieee80211_supported_band {TYPE_3__* bitrates; } ;
struct ieee80211_rx_status {int mactime; int encoding; size_t rate_idx; int enc_flags; size_t band; int flag; int /*<<< orphan*/  nss; int /*<<< orphan*/  bw; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  ri ;
struct TYPE_6__ {int bitrate; } ;
struct TYPE_4__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 size_t NL80211_BAND_5GHZ ; 
#define  RATE_INFO_BW_10 132 
#define  RATE_INFO_BW_5 131 
 int /*<<< orphan*/  RATE_INFO_FLAGS_MCS ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_SHORT_GI ; 
 int /*<<< orphan*/  RATE_INFO_FLAGS_VHT_MCS ; 
 int RX_ENC_FLAG_SHORTPRE ; 
 int RX_ENC_FLAG_SHORT_GI ; 
#define  RX_ENC_HT 130 
#define  RX_ENC_LEGACY 129 
#define  RX_ENC_VHT 128 
 int RX_FLAG_MACTIME_END ; 
 int RX_FLAG_MACTIME_PLCP_START ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ONCE (int,char*,unsigned long long,size_t,int /*<<< orphan*/ ) ; 
 unsigned int cfg80211_calculate_bitrate (struct rate_info*) ; 
 int /*<<< orphan*/  ieee80211_have_rx_timestamp (struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  memset (struct rate_info*,int /*<<< orphan*/ ,int) ; 

u64 ieee80211_calculate_rx_timestamp(struct ieee80211_local *local,
				     struct ieee80211_rx_status *status,
				     unsigned int mpdu_len,
				     unsigned int mpdu_offset)
{
	u64 ts = status->mactime;
	struct rate_info ri;
	u16 rate;

	if (WARN_ON(!ieee80211_have_rx_timestamp(status)))
		return 0;

	memset(&ri, 0, sizeof(ri));

	ri.bw = status->bw;

	/* Fill cfg80211 rate info */
	switch (status->encoding) {
	case RX_ENC_HT:
		ri.mcs = status->rate_idx;
		ri.flags |= RATE_INFO_FLAGS_MCS;
		if (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;
		break;
	case RX_ENC_VHT:
		ri.flags |= RATE_INFO_FLAGS_VHT_MCS;
		ri.mcs = status->rate_idx;
		ri.nss = status->nss;
		if (status->enc_flags & RX_ENC_FLAG_SHORT_GI)
			ri.flags |= RATE_INFO_FLAGS_SHORT_GI;
		break;
	default:
		WARN_ON(1);
		/* fall through */
	case RX_ENC_LEGACY: {
		struct ieee80211_supported_band *sband;
		int shift = 0;
		int bitrate;

		switch (status->bw) {
		case RATE_INFO_BW_10:
			shift = 1;
			break;
		case RATE_INFO_BW_5:
			shift = 2;
			break;
		}

		sband = local->hw.wiphy->bands[status->band];
		bitrate = sband->bitrates[status->rate_idx].bitrate;
		ri.legacy = DIV_ROUND_UP(bitrate, (1 << shift));

		if (status->flag & RX_FLAG_MACTIME_PLCP_START) {
			/* TODO: handle HT/VHT preambles */
			if (status->band == NL80211_BAND_5GHZ) {
				ts += 20 << shift;
				mpdu_offset += 2;
			} else if (status->enc_flags & RX_ENC_FLAG_SHORTPRE) {
				ts += 96;
			} else {
				ts += 192;
			}
		}
		break;
		}
	}

	rate = cfg80211_calculate_bitrate(&ri);
	if (WARN_ONCE(!rate,
		      "Invalid bitrate: flags=0x%llx, idx=%d, vht_nss=%d\n",
		      (unsigned long long)status->flag, status->rate_idx,
		      status->nss))
		return 0;

	/* rewind from end of MPDU */
	if (status->flag & RX_FLAG_MACTIME_END)
		ts -= mpdu_len * 8 * 10 / rate;

	ts += mpdu_offset * 8 * 10 / rate;

	return ts;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct minstrel_priv {scalar_t__ has_mrr; } ;
struct minstrel_ht_sta {int overhead; int overhead_rtscts; int sample_count; int sample_wait; int sample_tries; int tx_flags; int* supported; int cck_supported_short; int /*<<< orphan*/  sample_table; int /*<<< orphan*/  r; TYPE_3__* groups; int /*<<< orphan*/  avg_ampdu_len; int /*<<< orphan*/  last_stats_update; struct ieee80211_sta* sta; } ;
struct minstrel_ht_sta_priv {int is_ht; struct minstrel_ht_sta legacy; int /*<<< orphan*/  sample_table; int /*<<< orphan*/  ratelist; struct minstrel_ht_sta ht; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; } ;
struct TYPE_7__ {scalar_t__ tx_mcs_map; } ;
struct ieee80211_sta_vht_cap {int cap; TYPE_2__ vht_mcs; scalar_t__ vht_supported; } ;
struct ieee80211_mcs_info {int* rx_mask; } ;
struct TYPE_6__ {int cap; int /*<<< orphan*/  ht_supported; struct ieee80211_mcs_info mcs; } ;
struct ieee80211_sta {scalar_t__ bandwidth; scalar_t__ smps_mode; TYPE_1__ ht_cap; struct ieee80211_sta_vht_cap vht_cap; } ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_9__ {void (* rate_init ) (void*,struct ieee80211_supported_band*,struct cfg80211_chan_def*,struct ieee80211_sta*,struct minstrel_ht_sta*) ;} ;
struct TYPE_8__ {int flags; int streams; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int BW_20 ; 
 int BW_40 ; 
 int BW_80 ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 scalar_t__ IEEE80211_SMPS_STATIC ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 scalar_t__ IEEE80211_STA_RX_BW_80 ; 
 int IEEE80211_TX_CTL_LDPC ; 
 int IEEE80211_TX_CTL_STBC_SHIFT ; 
 int IEEE80211_TX_RC_160_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_MASK ; 
 int IEEE80211_VHT_CAP_RXSTBC_SHIFT ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 int MINSTREL_CCK_GROUP ; 
 int /*<<< orphan*/  MINSTREL_FRAC (int,int) ; 
 int MINSTREL_GROUPS_NB ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* ieee80211_frame_duration (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_4__ mac80211_minstrel ; 
 int /*<<< orphan*/  memset (struct minstrel_ht_sta*,int /*<<< orphan*/ ,int) ; 
 int minstrel_get_valid_vht_rates (int,int,scalar_t__) ; 
 int /*<<< orphan*/  minstrel_ht_update_cck (struct minstrel_priv*,struct minstrel_ht_sta*,struct ieee80211_supported_band*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_update_rates (struct minstrel_priv*,struct minstrel_ht_sta*) ; 
 int /*<<< orphan*/  minstrel_ht_update_stats (struct minstrel_priv*,struct minstrel_ht_sta*,int) ; 
 TYPE_3__* minstrel_mcs_groups ; 
 scalar_t__ minstrel_vht_only ; 
 void stub1 (void*,struct ieee80211_supported_band*,struct cfg80211_chan_def*,struct ieee80211_sta*,struct minstrel_ht_sta*) ; 

__attribute__((used)) static void
minstrel_ht_update_caps(void *priv, struct ieee80211_supported_band *sband,
			struct cfg80211_chan_def *chandef,
                        struct ieee80211_sta *sta, void *priv_sta)
{
	struct minstrel_priv *mp = priv;
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	struct ieee80211_mcs_info *mcs = &sta->ht_cap.mcs;
	u16 ht_cap = sta->ht_cap.cap;
	struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	int use_vht;
	int n_supported = 0;
	int ack_dur;
	int stbc;
	int i;
	bool ldpc;

	/* fall back to the old minstrel for legacy stations */
	if (!sta->ht_cap.ht_supported)
		goto use_legacy;

	BUILD_BUG_ON(ARRAY_SIZE(minstrel_mcs_groups) != MINSTREL_GROUPS_NB);

	if (vht_cap->vht_supported)
		use_vht = vht_cap->vht_mcs.tx_mcs_map != cpu_to_le16(~0);
	else
		use_vht = 0;

	msp->is_ht = true;
	memset(mi, 0, sizeof(*mi));

	mi->sta = sta;
	mi->last_stats_update = jiffies;

	ack_dur = ieee80211_frame_duration(sband->band, 10, 60, 1, 1, 0);
	mi->overhead = ieee80211_frame_duration(sband->band, 0, 60, 1, 1, 0);
	mi->overhead += ack_dur;
	mi->overhead_rtscts = mi->overhead + 2 * ack_dur;

	mi->avg_ampdu_len = MINSTREL_FRAC(1, 1);

	/* When using MRR, sample more on the first attempt, without delay */
	if (mp->has_mrr) {
		mi->sample_count = 16;
		mi->sample_wait = 0;
	} else {
		mi->sample_count = 8;
		mi->sample_wait = 8;
	}
	mi->sample_tries = 4;

	if (!use_vht) {
		stbc = (ht_cap & IEEE80211_HT_CAP_RX_STBC) >>
			IEEE80211_HT_CAP_RX_STBC_SHIFT;

		ldpc = ht_cap & IEEE80211_HT_CAP_LDPC_CODING;
	} else {
		stbc = (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK) >>
			IEEE80211_VHT_CAP_RXSTBC_SHIFT;

		ldpc = vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC;
	}

	mi->tx_flags |= stbc << IEEE80211_TX_CTL_STBC_SHIFT;
	if (ldpc)
		mi->tx_flags |= IEEE80211_TX_CTL_LDPC;

	for (i = 0; i < ARRAY_SIZE(mi->groups); i++) {
		u32 gflags = minstrel_mcs_groups[i].flags;
		int bw, nss;

		mi->supported[i] = 0;
		if (i == MINSTREL_CCK_GROUP) {
			minstrel_ht_update_cck(mp, mi, sband, sta);
			continue;
		}

		if (gflags & IEEE80211_TX_RC_SHORT_GI) {
			if (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH) {
				if (!(ht_cap & IEEE80211_HT_CAP_SGI_40))
					continue;
			} else {
				if (!(ht_cap & IEEE80211_HT_CAP_SGI_20))
					continue;
			}
		}

		if (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH &&
		    sta->bandwidth < IEEE80211_STA_RX_BW_40)
			continue;

		nss = minstrel_mcs_groups[i].streams;

		/* Mark MCS > 7 as unsupported if STA is in static SMPS mode */
		if (sta->smps_mode == IEEE80211_SMPS_STATIC && nss > 1)
			continue;

		/* HT rate */
		if (gflags & IEEE80211_TX_RC_MCS) {
			if (use_vht && minstrel_vht_only)
				continue;

			mi->supported[i] = mcs->rx_mask[nss - 1];
			if (mi->supported[i])
				n_supported++;
			continue;
		}

		/* VHT rate */
		if (!vht_cap->vht_supported ||
		    WARN_ON(!(gflags & IEEE80211_TX_RC_VHT_MCS)) ||
		    WARN_ON(gflags & IEEE80211_TX_RC_160_MHZ_WIDTH))
			continue;

		if (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH) {
			if (sta->bandwidth < IEEE80211_STA_RX_BW_80 ||
			    ((gflags & IEEE80211_TX_RC_SHORT_GI) &&
			     !(vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_80))) {
				continue;
			}
		}

		if (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = BW_40;
		else if (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			bw = BW_80;
		else
			bw = BW_20;

		mi->supported[i] = minstrel_get_valid_vht_rates(bw, nss,
				vht_cap->vht_mcs.tx_mcs_map);

		if (mi->supported[i])
			n_supported++;
	}

	if (!n_supported)
		goto use_legacy;

	mi->supported[MINSTREL_CCK_GROUP] |= mi->cck_supported_short << 4;

	/* create an initial rate table with the lowest supported rates */
	minstrel_ht_update_stats(mp, mi, true);
	minstrel_ht_update_rates(mp, mi);

	return;

use_legacy:
	msp->is_ht = false;
	memset(&msp->legacy, 0, sizeof(msp->legacy));
	msp->legacy.r = msp->ratelist;
	msp->legacy.sample_table = msp->sample_table;
	return mac80211_minstrel.rate_init(priv, sband, chandef, sta,
					   &msp->legacy);
}
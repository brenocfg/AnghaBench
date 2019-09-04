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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {size_t n_channels; size_t band; struct ieee80211_channel* channels; } ;
struct ieee80211_channel {int flags; int hw_value; int orig_flags; } ;
struct brcmu_chan {int chspec; scalar_t__ band; scalar_t__ bw; int control_ch_num; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_chanspec_list {int /*<<< orphan*/ * element; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;int /*<<< orphan*/  (* decchspec ) (struct brcmu_chan*) ;} ;
struct brcmf_cfg80211_info {TYPE_1__ d11inf; int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_DCMD_MEDLEN ; 
 scalar_t__ BRCMU_CHAN_BAND_2G ; 
 scalar_t__ BRCMU_CHAN_BAND_5G ; 
 scalar_t__ BRCMU_CHAN_BW_20 ; 
 scalar_t__ BRCMU_CHAN_BW_40 ; 
 scalar_t__ BRCMU_CHAN_BW_80 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40 ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 size_t WLC_BW_40MHZ_BIT ; 
 size_t WLC_BW_80MHZ_BIT ; 
 size_t WL_CHAN_PASSIVE ; 
 size_t WL_CHAN_RADAR ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int brcmf_fil_bsscfg_int_get (struct brcmf_if*,char*,size_t*) ; 
 int brcmf_fil_iovar_data_get (struct brcmf_if*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct brcmf_if* brcmf_get_ifp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_update_bw40_channel_flag (struct ieee80211_channel*,struct brcmu_chan*) ; 
 struct wiphy* cfg_to_wiphy (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 
 int /*<<< orphan*/  stub2 (struct brcmu_chan*) ; 

__attribute__((used)) static int brcmf_construct_chaninfo(struct brcmf_cfg80211_info *cfg,
				    u32 bw_cap[])
{
	struct brcmf_if *ifp = brcmf_get_ifp(cfg->pub, 0);
	struct ieee80211_supported_band *band;
	struct ieee80211_channel *channel;
	struct wiphy *wiphy;
	struct brcmf_chanspec_list *list;
	struct brcmu_chan ch;
	int err;
	u8 *pbuf;
	u32 i, j;
	u32 total;
	u32 chaninfo;

	pbuf = kzalloc(BRCMF_DCMD_MEDLEN, GFP_KERNEL);

	if (pbuf == NULL)
		return -ENOMEM;

	list = (struct brcmf_chanspec_list *)pbuf;

	err = brcmf_fil_iovar_data_get(ifp, "chanspecs", pbuf,
				       BRCMF_DCMD_MEDLEN);
	if (err) {
		brcmf_err("get chanspecs error (%d)\n", err);
		goto fail_pbuf;
	}

	wiphy = cfg_to_wiphy(cfg);
	band = wiphy->bands[NL80211_BAND_2GHZ];
	if (band)
		for (i = 0; i < band->n_channels; i++)
			band->channels[i].flags = IEEE80211_CHAN_DISABLED;
	band = wiphy->bands[NL80211_BAND_5GHZ];
	if (band)
		for (i = 0; i < band->n_channels; i++)
			band->channels[i].flags = IEEE80211_CHAN_DISABLED;

	total = le32_to_cpu(list->count);
	for (i = 0; i < total; i++) {
		ch.chspec = (u16)le32_to_cpu(list->element[i]);
		cfg->d11inf.decchspec(&ch);

		if (ch.band == BRCMU_CHAN_BAND_2G) {
			band = wiphy->bands[NL80211_BAND_2GHZ];
		} else if (ch.band == BRCMU_CHAN_BAND_5G) {
			band = wiphy->bands[NL80211_BAND_5GHZ];
		} else {
			brcmf_err("Invalid channel Spec. 0x%x.\n", ch.chspec);
			continue;
		}
		if (!band)
			continue;
		if (!(bw_cap[band->band] & WLC_BW_40MHZ_BIT) &&
		    ch.bw == BRCMU_CHAN_BW_40)
			continue;
		if (!(bw_cap[band->band] & WLC_BW_80MHZ_BIT) &&
		    ch.bw == BRCMU_CHAN_BW_80)
			continue;

		channel = NULL;
		for (j = 0; j < band->n_channels; j++) {
			if (band->channels[j].hw_value == ch.control_ch_num) {
				channel = &band->channels[j];
				break;
			}
		}
		if (!channel) {
			/* It seems firmware supports some channel we never
			 * considered. Something new in IEEE standard?
			 */
			brcmf_err("Ignoring unexpected firmware channel %d\n",
				  ch.control_ch_num);
			continue;
		}

		if (channel->orig_flags & IEEE80211_CHAN_DISABLED)
			continue;

		/* assuming the chanspecs order is HT20,
		 * HT40 upper, HT40 lower, and VHT80.
		 */
		if (ch.bw == BRCMU_CHAN_BW_80) {
			channel->flags &= ~IEEE80211_CHAN_NO_80MHZ;
		} else if (ch.bw == BRCMU_CHAN_BW_40) {
			brcmf_update_bw40_channel_flag(channel, &ch);
		} else {
			/* enable the channel and disable other bandwidths
			 * for now as mentioned order assure they are enabled
			 * for subsequent chanspecs.
			 */
			channel->flags = IEEE80211_CHAN_NO_HT40 |
					 IEEE80211_CHAN_NO_80MHZ |
					 IEEE80211_CHAN_NO_160MHZ;
			ch.bw = BRCMU_CHAN_BW_20;
			cfg->d11inf.encchspec(&ch);
			chaninfo = ch.chspec;
			err = brcmf_fil_bsscfg_int_get(ifp, "per_chan_info",
						       &chaninfo);
			if (!err) {
				if (chaninfo & WL_CHAN_RADAR)
					channel->flags |=
						(IEEE80211_CHAN_RADAR |
						 IEEE80211_CHAN_NO_IR);
				if (chaninfo & WL_CHAN_PASSIVE)
					channel->flags |=
						IEEE80211_CHAN_NO_IR;
			}
		}
	}

fail_pbuf:
	kfree(pbuf);
	return err;
}
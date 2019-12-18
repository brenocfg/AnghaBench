#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ieee802_11_elems {int* max_channel_switch_time; TYPE_3__* mesh_chansw_params_ie; TYPE_2__* ch_switch_ie; TYPE_1__* ext_chansw_ie; struct ieee80211_wide_bw_chansw_ie* wide_bw_chansw_ie; struct ieee80211_sec_chan_offs_ie* sec_chan_offs; } ;
struct ieee80211_wide_bw_chansw_ie {int /*<<< orphan*/  new_center_freq_seg1; int /*<<< orphan*/  new_center_freq_seg0; int /*<<< orphan*/  new_channel_width; } ;
struct ieee80211_vht_operation {int /*<<< orphan*/  center_freq_seg1_idx; int /*<<< orphan*/  center_freq_seg0_idx; int /*<<< orphan*/  chan_width; } ;
struct TYPE_12__ {scalar_t__ width; } ;
struct TYPE_13__ {TYPE_4__ chandef; } ;
struct TYPE_14__ {TYPE_5__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_7__* local; TYPE_6__ vif; } ;
struct ieee80211_sec_chan_offs_ie {int sec_chan_offs; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct cfg80211_chan_def {scalar_t__ width; int /*<<< orphan*/ * chan; } ;
struct ieee80211_csa_ie {int mode; int max_switch_time; struct cfg80211_chan_def chandef; void* reason_code; void* pre_value; int /*<<< orphan*/  ttl; int /*<<< orphan*/  count; } ;
struct ieee80211_channel {int flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_16__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_15__ {TYPE_8__ hw; } ;
struct TYPE_11__ {int mesh_flags; int /*<<< orphan*/  mesh_reason; int /*<<< orphan*/  mesh_pre_value; int /*<<< orphan*/  mesh_ttl; } ;
struct TYPE_10__ {int mode; int /*<<< orphan*/  count; int /*<<< orphan*/  new_ch_num; } ;
struct TYPE_9__ {int mode; int /*<<< orphan*/  count; int /*<<< orphan*/  new_ch_num; int /*<<< orphan*/ * new_operating_class; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_CHAN_DISABLED ; 
#define  IEEE80211_HT_PARAM_CHA_SEC_ABOVE 132 
#define  IEEE80211_HT_PARAM_CHA_SEC_BELOW 131 
#define  IEEE80211_HT_PARAM_CHA_SEC_NONE 130 
 int IEEE80211_STA_DISABLE_160MHZ ; 
 int IEEE80211_STA_DISABLE_40MHZ ; 
 int IEEE80211_STA_DISABLE_80P80MHZ ; 
 int IEEE80211_STA_DISABLE_HT ; 
 int IEEE80211_STA_DISABLE_VHT ; 
 int /*<<< orphan*/  NL80211_CHAN_HT20 ; 
 int /*<<< orphan*/  NL80211_CHAN_HT40MINUS ; 
 int /*<<< orphan*/  NL80211_CHAN_HT40PLUS ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
#define  NL80211_CHAN_WIDTH_10 129 
 scalar_t__ NL80211_CHAN_WIDTH_160 ; 
#define  NL80211_CHAN_WIDTH_5 128 
 scalar_t__ NL80211_CHAN_WIDTH_80P80 ; 
 int WLAN_EID_CHAN_SWITCH_PARAM_REASON ; 
 int /*<<< orphan*/  cfg80211_chandef_compatible (struct cfg80211_chan_def*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_chandef_downgrade (struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  ieee80211_chandef_vht_oper (TYPE_8__*,struct ieee80211_vht_operation*,struct ieee80211_ht_operation*,struct cfg80211_chan_def*) ; 
 int ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_operating_class_to_band (int /*<<< orphan*/ *,int*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_csa_ie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ *,...) ; 

int ieee80211_parse_ch_switch_ie(struct ieee80211_sub_if_data *sdata,
				 struct ieee802_11_elems *elems,
				 enum nl80211_band current_band,
				 u32 sta_flags, u8 *bssid,
				 struct ieee80211_csa_ie *csa_ie)
{
	enum nl80211_band new_band = current_band;
	int new_freq;
	u8 new_chan_no;
	struct ieee80211_channel *new_chan;
	struct cfg80211_chan_def new_vht_chandef = {};
	const struct ieee80211_sec_chan_offs_ie *sec_chan_offs;
	const struct ieee80211_wide_bw_chansw_ie *wide_bw_chansw_ie;
	int secondary_channel_offset = -1;

	memset(csa_ie, 0, sizeof(*csa_ie));

	sec_chan_offs = elems->sec_chan_offs;
	wide_bw_chansw_ie = elems->wide_bw_chansw_ie;

	if (sta_flags & (IEEE80211_STA_DISABLE_HT |
			 IEEE80211_STA_DISABLE_40MHZ)) {
		sec_chan_offs = NULL;
		wide_bw_chansw_ie = NULL;
	}

	if (sta_flags & IEEE80211_STA_DISABLE_VHT)
		wide_bw_chansw_ie = NULL;

	if (elems->ext_chansw_ie) {
		if (!ieee80211_operating_class_to_band(
				elems->ext_chansw_ie->new_operating_class,
				&new_band)) {
			sdata_info(sdata,
				   "cannot understand ECSA IE operating class, %d, ignoring\n",
				   elems->ext_chansw_ie->new_operating_class);
		}
		new_chan_no = elems->ext_chansw_ie->new_ch_num;
		csa_ie->count = elems->ext_chansw_ie->count;
		csa_ie->mode = elems->ext_chansw_ie->mode;
	} else if (elems->ch_switch_ie) {
		new_chan_no = elems->ch_switch_ie->new_ch_num;
		csa_ie->count = elems->ch_switch_ie->count;
		csa_ie->mode = elems->ch_switch_ie->mode;
	} else {
		/* nothing here we understand */
		return 1;
	}

	/* Mesh Channel Switch Parameters Element */
	if (elems->mesh_chansw_params_ie) {
		csa_ie->ttl = elems->mesh_chansw_params_ie->mesh_ttl;
		csa_ie->mode = elems->mesh_chansw_params_ie->mesh_flags;
		csa_ie->pre_value = le16_to_cpu(
				elems->mesh_chansw_params_ie->mesh_pre_value);

		if (elems->mesh_chansw_params_ie->mesh_flags &
				WLAN_EID_CHAN_SWITCH_PARAM_REASON)
			csa_ie->reason_code = le16_to_cpu(
				elems->mesh_chansw_params_ie->mesh_reason);
	}

	new_freq = ieee80211_channel_to_frequency(new_chan_no, new_band);
	new_chan = ieee80211_get_channel(sdata->local->hw.wiphy, new_freq);
	if (!new_chan || new_chan->flags & IEEE80211_CHAN_DISABLED) {
		sdata_info(sdata,
			   "BSS %pM switches to unsupported channel (%d MHz), disconnecting\n",
			   bssid, new_freq);
		return -EINVAL;
	}

	if (sec_chan_offs) {
		secondary_channel_offset = sec_chan_offs->sec_chan_offs;
	} else if (!(sta_flags & IEEE80211_STA_DISABLE_HT)) {
		/* If the secondary channel offset IE is not present,
		 * we can't know what's the post-CSA offset, so the
		 * best we can do is use 20MHz.
		*/
		secondary_channel_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
	}

	switch (secondary_channel_offset) {
	default:
		/* secondary_channel_offset was present but is invalid */
	case IEEE80211_HT_PARAM_CHA_SEC_NONE:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT20);
		break;
	case IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT40PLUS);
		break;
	case IEEE80211_HT_PARAM_CHA_SEC_BELOW:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_HT40MINUS);
		break;
	case -1:
		cfg80211_chandef_create(&csa_ie->chandef, new_chan,
					NL80211_CHAN_NO_HT);
		/* keep width for 5/10 MHz channels */
		switch (sdata->vif.bss_conf.chandef.width) {
		case NL80211_CHAN_WIDTH_5:
		case NL80211_CHAN_WIDTH_10:
			csa_ie->chandef.width =
				sdata->vif.bss_conf.chandef.width;
			break;
		default:
			break;
		}
		break;
	}

	if (wide_bw_chansw_ie) {
		struct ieee80211_vht_operation vht_oper = {
			.chan_width =
				wide_bw_chansw_ie->new_channel_width,
			.center_freq_seg0_idx =
				wide_bw_chansw_ie->new_center_freq_seg0,
			.center_freq_seg1_idx =
				wide_bw_chansw_ie->new_center_freq_seg1,
			/* .basic_mcs_set doesn't matter */
		};
		struct ieee80211_ht_operation ht_oper = {};

		/* default, for the case of IEEE80211_VHT_CHANWIDTH_USE_HT,
		 * to the previously parsed chandef
		 */
		new_vht_chandef = csa_ie->chandef;

		/* ignore if parsing fails */
		if (!ieee80211_chandef_vht_oper(&sdata->local->hw,
						&vht_oper, &ht_oper,
						&new_vht_chandef))
			new_vht_chandef.chan = NULL;

		if (sta_flags & IEEE80211_STA_DISABLE_80P80MHZ &&
		    new_vht_chandef.width == NL80211_CHAN_WIDTH_80P80)
			ieee80211_chandef_downgrade(&new_vht_chandef);
		if (sta_flags & IEEE80211_STA_DISABLE_160MHZ &&
		    new_vht_chandef.width == NL80211_CHAN_WIDTH_160)
			ieee80211_chandef_downgrade(&new_vht_chandef);
	}

	/* if VHT data is there validate & use it */
	if (new_vht_chandef.chan) {
		if (!cfg80211_chandef_compatible(&new_vht_chandef,
						 &csa_ie->chandef)) {
			sdata_info(sdata,
				   "BSS %pM: CSA has inconsistent channel data, disconnecting\n",
				   bssid);
			return -EINVAL;
		}
		csa_ie->chandef = new_vht_chandef;
	}

	if (elems->max_channel_switch_time)
		csa_ie->max_switch_time =
			(elems->max_channel_switch_time[0] << 0) |
			(elems->max_channel_switch_time[1] <<  8) |
			(elems->max_channel_switch_time[2] << 16);

	return 0;
}
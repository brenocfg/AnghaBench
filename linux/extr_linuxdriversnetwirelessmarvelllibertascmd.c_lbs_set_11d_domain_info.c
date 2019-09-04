#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct TYPE_7__ {void* len; void* type; } ;
struct mrvl_ie_domain_param_set {char* country_code; TYPE_3__ header; struct ieee80211_country_ie_triplet* triplet; } ;
struct lbs_private {char* country_code; TYPE_1__* wdev; } ;
struct ieee80211_supported_band {size_t n_channels; struct ieee80211_channel* channels; } ;
struct TYPE_6__ {size_t first_channel; size_t num_channels; size_t max_power; } ;
struct ieee80211_country_ie_triplet {TYPE_2__ chans; } ;
struct ieee80211_channel {int flags; size_t hw_value; size_t max_power; } ;
struct TYPE_8__ {void* size; } ;
struct cmd_ds_802_11d_domain_info {TYPE_4__ hdr; struct mrvl_ie_domain_param_set domain; void* action; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11D_DOMAIN_INFO ; 
 int CMD_ACT_SET ; 
 int IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  LBS_DEB_11D ; 
 size_t MAX_11D_TRIPLETS ; 
 int NUM_NL80211_BANDS ; 
 int TLV_TYPE_DOMAIN ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11d_domain_info*) ; 
 int /*<<< orphan*/  lbs_deb_11d (char*,size_t,...) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11d_domain_info*,int /*<<< orphan*/ ,int) ; 

int lbs_set_11d_domain_info(struct lbs_private *priv)
{
	struct wiphy *wiphy = priv->wdev->wiphy;
	struct ieee80211_supported_band **bands = wiphy->bands;
	struct cmd_ds_802_11d_domain_info cmd;
	struct mrvl_ie_domain_param_set *domain = &cmd.domain;
	struct ieee80211_country_ie_triplet *t;
	enum nl80211_band band;
	struct ieee80211_channel *ch;
	u8 num_triplet = 0;
	u8 num_parsed_chan = 0;
	u8 first_channel = 0, next_chan = 0, max_pwr = 0;
	u8 i, flag = 0;
	size_t triplet_size;
	int ret = 0;

	if (!priv->country_code[0])
		goto out;

	memset(&cmd, 0, sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);

	lbs_deb_11d("Setting country code '%c%c'\n",
		    priv->country_code[0], priv->country_code[1]);

	domain->header.type = cpu_to_le16(TLV_TYPE_DOMAIN);

	/* Set country code */
	domain->country_code[0] = priv->country_code[0];
	domain->country_code[1] = priv->country_code[1];
	domain->country_code[2] = ' ';

	/* Now set up the channel triplets; firmware is somewhat picky here
	 * and doesn't validate channel numbers and spans; hence it would
	 * interpret a triplet of (36, 4, 20) as channels 36, 37, 38, 39.  Since
	 * the last 3 aren't valid channels, the driver is responsible for
	 * splitting that up into 4 triplet pairs of (36, 1, 20) + (40, 1, 20)
	 * etc.
	 */
	for (band = 0;
	     (band < NUM_NL80211_BANDS) && (num_triplet < MAX_11D_TRIPLETS);
	     band++) {

		if (!bands[band])
			continue;

		for (i = 0;
		     (i < bands[band]->n_channels) && (num_triplet < MAX_11D_TRIPLETS);
		     i++) {
			ch = &bands[band]->channels[i];
			if (ch->flags & IEEE80211_CHAN_DISABLED)
				continue;

			if (!flag) {
				flag = 1;
				next_chan = first_channel = (u32) ch->hw_value;
				max_pwr = ch->max_power;
				num_parsed_chan = 1;
				continue;
			}

			if ((ch->hw_value == next_chan + 1) &&
					(ch->max_power == max_pwr)) {
				/* Consolidate adjacent channels */
				next_chan++;
				num_parsed_chan++;
			} else {
				/* Add this triplet */
				lbs_deb_11d("11D triplet (%d, %d, %d)\n",
					first_channel, num_parsed_chan,
					max_pwr);
				t = &domain->triplet[num_triplet];
				t->chans.first_channel = first_channel;
				t->chans.num_channels = num_parsed_chan;
				t->chans.max_power = max_pwr;
				num_triplet++;
				flag = 0;
			}
		}

		if (flag) {
			/* Add last triplet */
			lbs_deb_11d("11D triplet (%d, %d, %d)\n", first_channel,
				num_parsed_chan, max_pwr);
			t = &domain->triplet[num_triplet];
			t->chans.first_channel = first_channel;
			t->chans.num_channels = num_parsed_chan;
			t->chans.max_power = max_pwr;
			num_triplet++;
		}
	}

	lbs_deb_11d("# triplets %d\n", num_triplet);

	/* Set command header sizes */
	triplet_size = num_triplet * sizeof(struct ieee80211_country_ie_triplet);
	domain->header.len = cpu_to_le16(sizeof(domain->country_code) +
					triplet_size);

	lbs_deb_hex(LBS_DEB_11D, "802.11D domain param set",
			(u8 *) &cmd.domain.country_code,
			le16_to_cpu(domain->header.len));

	cmd.hdr.size = cpu_to_le16(sizeof(cmd.hdr) +
				   sizeof(cmd.action) +
				   sizeof(cmd.domain.header) +
				   sizeof(cmd.domain.country_code) +
				   triplet_size);

	ret = lbs_cmd_with_response(priv, CMD_802_11D_DOMAIN_INFO, &cmd);

out:
	return ret;
}
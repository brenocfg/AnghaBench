#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct survey_info {int dummy; } ;
struct ath_regulatory {int /*<<< orphan*/  current_rd; } ;
struct TYPE_13__ {scalar_t__ length; int operating_flags; int /*<<< orphan*/  mac_address; int /*<<< orphan*/ * reg_domain; int /*<<< orphan*/  tx_mask; int /*<<< orphan*/  rx_mask; } ;
struct TYPE_9__ {struct ath_regulatory regulatory; } ;
struct ar9170 {int num_channels; TYPE_5__ eeprom; TYPE_8__* hw; int /*<<< orphan*/  survey; TYPE_1__ common; } ;
struct TYPE_15__ {TYPE_4__* wiphy; } ;
struct TYPE_10__ {unsigned int tx_params; } ;
struct TYPE_11__ {TYPE_2__ mcs; } ;
struct TYPE_14__ {scalar_t__ n_channels; TYPE_3__ ht_cap; } ;
struct TYPE_12__ {TYPE_6__** bands; } ;

/* Variables and functions */
 int AR9170_OPFLAG_2GHZ ; 
 int AR9170_OPFLAG_5GHZ ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IEEE80211_HT_MCS_TX_MAX_STREAMS ; 
 unsigned int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 unsigned int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_6__ carl9170_band_2GHz ; 
 TYPE_6__ carl9170_band_5GHz ; 
 scalar_t__ cpu_to_le16 (int) ; 
 unsigned int hweight8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int carl9170_parse_eeprom(struct ar9170 *ar)
{
	struct ath_regulatory *regulatory = &ar->common.regulatory;
	unsigned int rx_streams, tx_streams, tx_params = 0;
	int bands = 0;
	int chans = 0;

	if (ar->eeprom.length == cpu_to_le16(0xffff))
		return -ENODATA;

	rx_streams = hweight8(ar->eeprom.rx_mask);
	tx_streams = hweight8(ar->eeprom.tx_mask);

	if (rx_streams != tx_streams) {
		tx_params = IEEE80211_HT_MCS_TX_RX_DIFF;

		WARN_ON(!(tx_streams >= 1 && tx_streams <=
			IEEE80211_HT_MCS_TX_MAX_STREAMS));

		tx_params = (tx_streams - 1) <<
			    IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;

		carl9170_band_2GHz.ht_cap.mcs.tx_params |= tx_params;
		carl9170_band_5GHz.ht_cap.mcs.tx_params |= tx_params;
	}

	if (ar->eeprom.operating_flags & AR9170_OPFLAG_2GHZ) {
		ar->hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&carl9170_band_2GHz;
		chans += carl9170_band_2GHz.n_channels;
		bands++;
	}
	if (ar->eeprom.operating_flags & AR9170_OPFLAG_5GHZ) {
		ar->hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&carl9170_band_5GHz;
		chans += carl9170_band_5GHz.n_channels;
		bands++;
	}

	if (!bands)
		return -EINVAL;

	ar->survey = kcalloc(chans, sizeof(struct survey_info), GFP_KERNEL);
	if (!ar->survey)
		return -ENOMEM;
	ar->num_channels = chans;

	regulatory->current_rd = le16_to_cpu(ar->eeprom.reg_domain[0]);

	/* second part of wiphy init */
	SET_IEEE80211_PERM_ADDR(ar->hw, ar->eeprom.mac_address);

	return 0;
}
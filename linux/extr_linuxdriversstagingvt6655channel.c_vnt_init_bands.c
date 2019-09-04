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
struct vnt_private {int byRFType; TYPE_2__* hw; } ;
struct ieee80211_channel {int max_power; void* flags; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ieee80211_channel*) ; 
 void* IEEE80211_CHAN_NO_HT40 ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
#define  RF_AIROHA 135 
#define  RF_AIROHA7230 134 
#define  RF_AL2230S 133 
#define  RF_NOTHING 132 
#define  RF_RFMD2959 131 
#define  RF_UW2451 130 
#define  RF_UW2452 129 
#define  RF_VT3226 128 
 struct ieee80211_channel* vnt_channels_2ghz ; 
 struct ieee80211_channel* vnt_channels_5ghz ; 
 int /*<<< orphan*/  vnt_supported_2ghz_band ; 
 int /*<<< orphan*/  vnt_supported_5ghz_band ; 

void vnt_init_bands(struct vnt_private *priv)
{
	struct ieee80211_channel *ch;
	int i;

	switch (priv->byRFType) {
	case RF_AIROHA7230:
	case RF_UW2452:
	case RF_NOTHING:
	default:
		ch = vnt_channels_5ghz;

		for (i = 0; i < ARRAY_SIZE(vnt_channels_5ghz); i++) {
			ch[i].max_power = 0x3f;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		}

		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] =
						&vnt_supported_5ghz_band;
	/* fallthrough */
	case RF_RFMD2959:
	case RF_AIROHA:
	case RF_AL2230S:
	case RF_UW2451:
	case RF_VT3226:
		ch = vnt_channels_2ghz;

		for (i = 0; i < ARRAY_SIZE(vnt_channels_2ghz); i++) {
			ch[i].max_power = 0x3f;
			ch[i].flags = IEEE80211_CHAN_NO_HT40;
		}

		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] =
						&vnt_supported_2ghz_band;
		break;
	}
}
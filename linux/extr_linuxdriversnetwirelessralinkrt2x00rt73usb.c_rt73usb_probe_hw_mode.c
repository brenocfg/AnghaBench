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
struct hw_mode_spec {int supported_rates; int num_channels; struct channel_info* channels_info; void* channels; int /*<<< orphan*/  supported_bands; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  dev; struct hw_mode_spec spec; } ;
struct channel_info {void* default_power1; void* max_power; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  EEPROM_MAC_ADDR_0 ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_A_START ; 
 int /*<<< orphan*/  EEPROM_TXPOWER_G_START ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MAX_TXPOWER ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  RF2527 ; 
 int /*<<< orphan*/  RF2528 ; 
 int /*<<< orphan*/  RF5225 ; 
 int /*<<< orphan*/  RF5226 ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  SUPPORT_BAND_2GHZ ; 
 int /*<<< orphan*/  SUPPORT_BAND_5GHZ ; 
 int SUPPORT_RATE_CCK ; 
 int SUPPORT_RATE_OFDM ; 
 void* TXPOWER_FROM_DEV (char) ; 
 int /*<<< orphan*/  ieee80211_hw_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct channel_info* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* rf_vals_5225_2527 ; 
 void* rf_vals_5226 ; 
 void* rf_vals_bg_2528 ; 
 char* rt2x00_eeprom_addr (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt73usb_probe_hw_mode(struct rt2x00_dev *rt2x00dev)
{
	struct hw_mode_spec *spec = &rt2x00dev->spec;
	struct channel_info *info;
	char *tx_power;
	unsigned int i;

	/*
	 * Initialize all hw fields.
	 *
	 * Don't set IEEE80211_HOST_BROADCAST_PS_BUFFERING unless we are
	 * capable of sending the buffered frames out after the DTIM
	 * transmission using rt2x00lib_beacondone. This will send out
	 * multicast and broadcast traffic immediately instead of buffering it
	 * infinitly and thus dropping it after some time.
	 */
	ieee80211_hw_set(rt2x00dev->hw, PS_NULLFUNC_STACK);
	ieee80211_hw_set(rt2x00dev->hw, SIGNAL_DBM);
	ieee80211_hw_set(rt2x00dev->hw, SUPPORTS_PS);

	SET_IEEE80211_DEV(rt2x00dev->hw, rt2x00dev->dev);
	SET_IEEE80211_PERM_ADDR(rt2x00dev->hw,
				rt2x00_eeprom_addr(rt2x00dev,
						   EEPROM_MAC_ADDR_0));

	/*
	 * Initialize hw_mode information.
	 */
	spec->supported_bands = SUPPORT_BAND_2GHZ;
	spec->supported_rates = SUPPORT_RATE_CCK | SUPPORT_RATE_OFDM;

	if (rt2x00_rf(rt2x00dev, RF2528)) {
		spec->num_channels = ARRAY_SIZE(rf_vals_bg_2528);
		spec->channels = rf_vals_bg_2528;
	} else if (rt2x00_rf(rt2x00dev, RF5226)) {
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_5226);
		spec->channels = rf_vals_5226;
	} else if (rt2x00_rf(rt2x00dev, RF2527)) {
		spec->num_channels = 14;
		spec->channels = rf_vals_5225_2527;
	} else if (rt2x00_rf(rt2x00dev, RF5225)) {
		spec->supported_bands |= SUPPORT_BAND_5GHZ;
		spec->num_channels = ARRAY_SIZE(rf_vals_5225_2527);
		spec->channels = rf_vals_5225_2527;
	}

	/*
	 * Create channel information array
	 */
	info = kcalloc(spec->num_channels, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	spec->channels_info = info;

	tx_power = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_G_START);
	for (i = 0; i < 14; i++) {
		info[i].max_power = MAX_TXPOWER;
		info[i].default_power1 = TXPOWER_FROM_DEV(tx_power[i]);
	}

	if (spec->num_channels > 14) {
		tx_power = rt2x00_eeprom_addr(rt2x00dev, EEPROM_TXPOWER_A_START);
		for (i = 14; i < spec->num_channels; i++) {
			info[i].max_power = MAX_TXPOWER;
			info[i].default_power1 =
					TXPOWER_FROM_DEV(tx_power[i - 14]);
		}
	}

	return 0;
}
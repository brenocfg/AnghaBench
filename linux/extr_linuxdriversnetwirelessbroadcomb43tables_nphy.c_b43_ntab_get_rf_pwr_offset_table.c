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
struct b43_phy {int rev; int radio_rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* b43_ntab_rf_pwr_offset_2057_rev14_2g ; 
 int /*<<< orphan*/  const* b43_ntab_rf_pwr_offset_2057_rev9_2g ; 
 int /*<<< orphan*/  const* b43_ntab_rf_pwr_offset_2057_rev9_5g ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

const s16 *b43_ntab_get_rf_pwr_offset_table(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		switch (phy->rev) {
		case 17:
			if (phy->radio_rev == 14)
				return b43_ntab_rf_pwr_offset_2057_rev14_2g;
			break;
		case 16:
			if (phy->radio_rev == 9)
				return b43_ntab_rf_pwr_offset_2057_rev9_2g;
			break;
		}

		b43err(dev->wl,
		       "No 2GHz RF power table available for this device\n");
		return NULL;
	} else {
		switch (phy->rev) {
		case 16:
			if (phy->radio_rev == 9)
				return b43_ntab_rf_pwr_offset_2057_rev9_5g;
			break;
		}

		b43err(dev->wl,
		       "No 5GHz RF power table available for this device\n");
		return NULL;
	}
}
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
typedef  int u8 ;
struct ieee80211_supported_band {scalar_t__ band; int n_iftype_data; TYPE_3__* iftype_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * phy_cap_info; } ;
struct TYPE_5__ {TYPE_1__ he_cap_elem; } ;
struct TYPE_6__ {TYPE_2__ he_cap; } ;

/* Variables and functions */
 int ANT_AB ; 
 int /*<<< orphan*/  IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_MAX_NSTS ; 
 int /*<<< orphan*/  IEEE80211_HE_PHY_CAP2_MIDAMBLE_RX_MAX_NSTS ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 TYPE_3__ iwl_he_capa ; 

__attribute__((used)) static void iwl_init_he_hw_capab(struct ieee80211_supported_band *sband,
				 u8 tx_chains, u8 rx_chains)
{
	if (sband->band == NL80211_BAND_2GHZ ||
	    sband->band == NL80211_BAND_5GHZ)
		sband->iftype_data = &iwl_he_capa;
	else
		return;

	sband->n_iftype_data = 1;

	/* If not 2x2, we need to indicate 1x1 in the Midamble RX Max NSTS */
	if ((tx_chains & rx_chains) != ANT_AB) {
		iwl_he_capa.he_cap.he_cap_elem.phy_cap_info[1] &=
			~IEEE80211_HE_PHY_CAP1_MIDAMBLE_RX_MAX_NSTS;
		iwl_he_capa.he_cap.he_cap_elem.phy_cap_info[2] &=
			~IEEE80211_HE_PHY_CAP2_MIDAMBLE_RX_MAX_NSTS;
	}
}
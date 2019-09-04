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
struct iwl_mvm {TYPE_1__* nvm_data; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_2__* bitrates; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_3__ {struct ieee80211_supported_band* bands; } ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 unsigned int SCAN_CONFIG_SUPPORTED_RATE (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 unsigned int rate_to_scan_rate_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le32 iwl_mvm_scan_config_rates(struct iwl_mvm *mvm)
{
	struct ieee80211_supported_band *band;
	unsigned int rates = 0;
	int i;

	band = &mvm->nvm_data->bands[NL80211_BAND_2GHZ];
	for (i = 0; i < band->n_bitrates; i++)
		rates |= rate_to_scan_rate_flag(band->bitrates[i].hw_value);
	band = &mvm->nvm_data->bands[NL80211_BAND_5GHZ];
	for (i = 0; i < band->n_bitrates; i++)
		rates |= rate_to_scan_rate_flag(band->bitrates[i].hw_value);

	/* Set both basic rates and supported rates */
	rates |= SCAN_CONFIG_SUPPORTED_RATE(rates);

	return cpu_to_le32(rates);
}
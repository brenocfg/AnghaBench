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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {TYPE_1__* nvm_data; } ;
struct ieee80211_supported_band {int n_channels; TYPE_2__* channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_3__ {struct ieee80211_supported_band* bands; } ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 

__attribute__((used)) static void iwl_mvm_fill_channels(struct iwl_mvm *mvm, u8 *channels)
{
	struct ieee80211_supported_band *band;
	int i, j = 0;

	band = &mvm->nvm_data->bands[NL80211_BAND_2GHZ];
	for (i = 0; i < band->n_channels; i++, j++)
		channels[j] = band->channels[i].hw_value;
	band = &mvm->nvm_data->bands[NL80211_BAND_5GHZ];
	for (i = 0; i < band->n_channels; i++, j++)
		channels[j] = band->channels[i].hw_value;
}
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
struct wiphy {TYPE_1__** bands; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {scalar_t__ n_channels; } ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 

unsigned int ieee80211_get_num_supported_channels(struct wiphy *wiphy)
{
	enum nl80211_band band;
	unsigned int n_channels = 0;

	for (band = 0; band < NUM_NL80211_BANDS; band++)
		if (wiphy->bands[band])
			n_channels += wiphy->bands[band]->n_channels;

	return n_channels;
}
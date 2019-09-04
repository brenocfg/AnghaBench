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
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct TYPE_2__ {size_t band; } ;
struct reg_beacon {TYPE_1__ chan; } ;
struct ieee80211_supported_band {unsigned int n_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_reg_beacon (struct wiphy*,unsigned int,struct reg_beacon*) ; 

__attribute__((used)) static void wiphy_update_new_beacon(struct wiphy *wiphy,
				    struct reg_beacon *reg_beacon)
{
	unsigned int i;
	struct ieee80211_supported_band *sband;

	if (!wiphy->bands[reg_beacon->chan.band])
		return;

	sband = wiphy->bands[reg_beacon->chan.band];

	for (i = 0; i < sband->n_channels; i++)
		handle_reg_beacon(wiphy, i, reg_beacon);
}
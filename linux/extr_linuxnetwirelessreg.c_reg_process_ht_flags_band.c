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
struct wiphy {int dummy; } ;
struct ieee80211_supported_band {unsigned int n_channels; int /*<<< orphan*/ * channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_process_ht_flags_channel (struct wiphy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reg_process_ht_flags_band(struct wiphy *wiphy,
				      struct ieee80211_supported_band *sband)
{
	unsigned int i;

	if (!sband)
		return;

	for (i = 0; i < sband->n_channels; i++)
		reg_process_ht_flags_channel(wiphy, &sband->channels[i]);
}
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
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_channel_custom (struct wiphy*,int /*<<< orphan*/ *,struct ieee80211_regdomain const*) ; 

__attribute__((used)) static void handle_band_custom(struct wiphy *wiphy,
			       struct ieee80211_supported_band *sband,
			       const struct ieee80211_regdomain *regd)
{
	unsigned int i;

	if (!sband)
		return;

	for (i = 0; i < sband->n_channels; i++)
		handle_channel_custom(wiphy, &sband->channels[i], regd);
}
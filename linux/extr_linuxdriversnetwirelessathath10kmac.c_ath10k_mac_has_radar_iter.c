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
struct ieee80211_hw {int dummy; } ;
struct ieee80211_chanctx_conf {scalar_t__ radar_enabled; } ;

/* Variables and functions */

__attribute__((used)) static void ath10k_mac_has_radar_iter(struct ieee80211_hw *hw,
				      struct ieee80211_chanctx_conf *conf,
				      void *data)
{
	bool *ret = data;

	if (!*ret && conf->radar_enabled)
		*ret = true;
}
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
struct ieee80211_hw {int dummy; } ;
struct ieee80211_local {struct ieee80211_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

struct ieee80211_hw *wiphy_to_ieee80211_hw(struct wiphy *wiphy)
{
	struct ieee80211_local *local;
	BUG_ON(!wiphy);

	local = wiphy_priv(wiphy);
	return &local->hw;
}
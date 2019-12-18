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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct ieee80211_local {scalar_t__ started; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int drv_set_antenna (struct ieee80211_local*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_set_antenna(struct wiphy *wiphy, u32 tx_ant, u32 rx_ant)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);

	if (local->started)
		return -EOPNOTSUPP;

	return drv_set_antenna(local, tx_ant, rx_ant);
}
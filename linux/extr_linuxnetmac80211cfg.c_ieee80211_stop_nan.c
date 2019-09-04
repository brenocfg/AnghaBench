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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int /*<<< orphan*/  drv_stop_nan (int /*<<< orphan*/ ,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_sdata_stop (struct ieee80211_sub_if_data*) ; 

__attribute__((used)) static void ieee80211_stop_nan(struct wiphy *wiphy,
			       struct wireless_dev *wdev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	drv_stop_nan(sdata->local, sdata);
	ieee80211_sdata_stop(sdata);
}
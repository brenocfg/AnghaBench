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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ieee80211_sub_if_data {TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  chanctx_mtx; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int ieee80211_check_combinations (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_do_open (struct wireless_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_start_p2p_device(struct wiphy *wiphy,
				      struct wireless_dev *wdev)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	int ret;

	mutex_lock(&sdata->local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, NULL, 0, 0);
	mutex_unlock(&sdata->local->chanctx_mtx);
	if (ret < 0)
		return ret;

	return ieee80211_do_open(wdev, true);
}
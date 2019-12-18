#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct cfg80211_nan_conf {int dummy; } ;
struct TYPE_4__ {struct cfg80211_nan_conf conf; } ;
struct TYPE_5__ {TYPE_1__ nan; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; TYPE_3__* local; } ;
struct TYPE_6__ {int /*<<< orphan*/  chanctx_mtx; } ;

/* Variables and functions */
 struct ieee80211_sub_if_data* IEEE80211_WDEV_TO_SUB_IF (struct wireless_dev*) ; 
 int drv_start_nan (TYPE_3__*,struct ieee80211_sub_if_data*,struct cfg80211_nan_conf*) ; 
 int ieee80211_check_combinations (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_do_open (struct wireless_dev*,int) ; 
 int /*<<< orphan*/  ieee80211_sdata_stop (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_start_nan(struct wiphy *wiphy,
			       struct wireless_dev *wdev,
			       struct cfg80211_nan_conf *conf)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	int ret;

	mutex_lock(&sdata->local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, NULL, 0, 0);
	mutex_unlock(&sdata->local->chanctx_mtx);
	if (ret < 0)
		return ret;

	ret = ieee80211_do_open(wdev, true);
	if (ret)
		return ret;

	ret = drv_start_nan(sdata->local, sdata, conf);
	if (ret)
		ieee80211_sdata_stop(sdata);

	sdata->u.nan.conf = *conf;

	return ret;
}
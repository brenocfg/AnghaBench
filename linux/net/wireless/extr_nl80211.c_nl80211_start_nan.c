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
typedef  int u32 ;
struct wireless_dev {scalar_t__ iftype; int is_running; int /*<<< orphan*/  opencount; TYPE_1__* wiphy; int /*<<< orphan*/  rfkill; } ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ iftype; int is_running; int /*<<< orphan*/  opencount; TYPE_1__* wiphy; int /*<<< orphan*/  rfkill; } ;
struct cfg80211_nan_conf {int bands; int /*<<< orphan*/  master_pref; } ;
struct TYPE_2__ {scalar_t__ nan_supported_bands; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERFKILL ; 
 size_t NL80211_ATTR_BANDS ; 
 size_t NL80211_ATTR_NAN_MASTER_PREF ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_IFTYPE_NAN ; 
 int nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int rdev_start_nan (struct wireless_dev*,struct wireless_dev*,struct cfg80211_nan_conf*) ; 
 scalar_t__ rfkill_blocked (int /*<<< orphan*/ ) ; 
 scalar_t__ wdev_running (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_start_nan(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	struct cfg80211_nan_conf conf = {};
	int err;

	if (wdev->iftype != NL80211_IFTYPE_NAN)
		return -EOPNOTSUPP;

	if (wdev_running(wdev))
		return -EEXIST;

	if (rfkill_blocked(rdev->rfkill))
		return -ERFKILL;

	if (!info->attrs[NL80211_ATTR_NAN_MASTER_PREF])
		return -EINVAL;

	conf.master_pref =
		nla_get_u8(info->attrs[NL80211_ATTR_NAN_MASTER_PREF]);

	if (info->attrs[NL80211_ATTR_BANDS]) {
		u32 bands = nla_get_u32(info->attrs[NL80211_ATTR_BANDS]);

		if (bands & ~(u32)wdev->wiphy->nan_supported_bands)
			return -EOPNOTSUPP;

		if (bands && !(bands & BIT(NL80211_BAND_2GHZ)))
			return -EINVAL;

		conf.bands = bands;
	}

	err = rdev_start_nan(rdev, wdev, &conf);
	if (err)
		return err;

	wdev->is_running = true;
	rdev->opencount++;

	return 0;
}
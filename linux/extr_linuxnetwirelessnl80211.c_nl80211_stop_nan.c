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
struct wireless_dev {scalar_t__ iftype; } ;
struct sk_buff {int dummy; } ;
struct genl_info {struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ iftype; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_IFTYPE_NAN ; 
 int /*<<< orphan*/  cfg80211_stop_nan (struct wireless_dev*,struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_stop_nan(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];

	if (wdev->iftype != NL80211_IFTYPE_NAN)
		return -EOPNOTSUPP;

	cfg80211_stop_nan(rdev, wdev);

	return 0;
}
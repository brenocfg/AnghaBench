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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int dummy; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* remain_on_channel ) (int /*<<< orphan*/ *,struct wireless_dev*,struct ieee80211_channel*,unsigned int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wireless_dev*,struct ieee80211_channel*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_remain_on_channel (int /*<<< orphan*/ *,struct wireless_dev*,struct ieee80211_channel*,unsigned int) ; 
 int /*<<< orphan*/  trace_rdev_return_int_cookie (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rdev_remain_on_channel(struct cfg80211_registered_device *rdev,
		       struct wireless_dev *wdev,
		       struct ieee80211_channel *chan,
		       unsigned int duration, u64 *cookie)
{
	int ret;
	trace_rdev_remain_on_channel(&rdev->wiphy, wdev, chan, duration);
	ret = rdev->ops->remain_on_channel(&rdev->wiphy, wdev, chan,
					   duration, cookie);
	trace_rdev_return_int_cookie(&rdev->wiphy, ret, *cookie);
	return ret;
}
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
struct wireless_dev {int /*<<< orphan*/  scan_req; scalar_t__ scan_msg; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  scan_req; scalar_t__ scan_msg; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  abort_scan; } ;

/* Variables and functions */
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  rdev_abort_scan (struct wireless_dev*,struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_abort_scan(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];

	if (!rdev->ops->abort_scan)
		return -EOPNOTSUPP;

	if (rdev->scan_msg)
		return 0;

	if (!rdev->scan_req)
		return -ENOENT;

	rdev_abort_scan(rdev, wdev);
	return 0;
}
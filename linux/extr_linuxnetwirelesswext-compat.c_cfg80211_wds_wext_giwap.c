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
struct TYPE_2__ {int /*<<< orphan*/  bssid; } ;
struct wireless_dev {scalar_t__ iftype; TYPE_1__ wext; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_WDS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfg80211_wds_wext_giwap(struct net_device *dev,
				   struct iw_request_info *info,
				   struct sockaddr *addr, char *extra)
{
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	if (WARN_ON(wdev->iftype != NL80211_IFTYPE_WDS))
		return -EINVAL;

	addr->sa_family = ARPHRD_ETHER;
	memcpy(&addr->sa_data, wdev->wext.bssid, ETH_ALEN);

	return 0;
}
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
struct wireless_dev {scalar_t__ iftype; } ;
struct net_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_cqm_txe_config; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int NL80211_CQM_TXE_MAX_INTVL ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int rdev_set_cqm_txe_config (struct net_device*,struct net_device*,int,int,int) ; 

__attribute__((used)) static int nl80211_set_cqm_txe(struct genl_info *info,
			       u32 rate, u32 pkts, u32 intvl)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;

	if (rate > 100 || intvl > NL80211_CQM_TXE_MAX_INTVL)
		return -EINVAL;

	if (!rdev->ops->set_cqm_txe_config)
		return -EOPNOTSUPP;

	if (wdev->iftype != NL80211_IFTYPE_STATION &&
	    wdev->iftype != NL80211_IFTYPE_P2P_CLIENT)
		return -EOPNOTSUPP;

	return rdev_set_cqm_txe_config(rdev, dev, rate, pkts, intvl);
}
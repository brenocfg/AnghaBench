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
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/  attrs; } ;
struct cfg80211_registered_device {int dummy; } ;

/* Variables and functions */
 struct cfg80211_registered_device* __cfg80211_rdev_from_attrs (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfg80211_registered_device *
cfg80211_get_dev_from_info(struct net *netns, struct genl_info *info)
{
	return __cfg80211_rdev_from_attrs(netns, info->attrs);
}
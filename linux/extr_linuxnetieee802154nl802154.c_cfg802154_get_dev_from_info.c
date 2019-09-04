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
struct cfg802154_registered_device {int dummy; } ;

/* Variables and functions */
 struct cfg802154_registered_device* __cfg802154_rdev_from_attrs (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfg802154_registered_device *
cfg802154_get_dev_from_info(struct net *netns, struct genl_info *info)
{
	return __cfg802154_rdev_from_attrs(netns, info->attrs);
}
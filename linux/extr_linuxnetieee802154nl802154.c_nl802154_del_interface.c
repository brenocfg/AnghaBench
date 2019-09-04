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
struct wpan_dev {int /*<<< orphan*/  netdev; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {struct wpan_dev** user_ptr; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  netdev; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  del_virtual_intf; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int rdev_del_virtual_intf (struct wpan_dev*,struct wpan_dev*) ; 

__attribute__((used)) static int nl802154_del_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	struct wpan_dev *wpan_dev = info->user_ptr[1];

	if (!rdev->ops->del_virtual_intf)
		return -EOPNOTSUPP;

	/* If we remove a wpan device without a netdev then clear
	 * user_ptr[1] so that nl802154_post_doit won't dereference it
	 * to check if it needs to do dev_put(). Otherwise it crashes
	 * since the wpan_dev has been freed, unlike with a netdev where
	 * we need the dev_put() for the netdev to really be freed.
	 */
	if (!wpan_dev->netdev)
		info->user_ptr[1] = NULL;

	return rdev_del_virtual_intf(rdev, wpan_dev);
}
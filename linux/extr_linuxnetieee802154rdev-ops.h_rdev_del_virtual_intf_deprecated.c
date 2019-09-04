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
struct net_device {int dummy; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_virtual_intf_deprecated ) (int /*<<< orphan*/ *,struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct net_device*) ; 

__attribute__((used)) static inline void
rdev_del_virtual_intf_deprecated(struct cfg802154_registered_device *rdev,
				 struct net_device *dev)
{
	rdev->ops->del_virtual_intf_deprecated(&rdev->wpan_phy, dev);
}
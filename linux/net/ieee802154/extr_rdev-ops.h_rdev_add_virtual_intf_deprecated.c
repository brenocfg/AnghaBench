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
struct TYPE_2__ {struct net_device* (* add_virtual_intf_deprecated ) (int /*<<< orphan*/ *,char const*,unsigned char,int) ;} ;

/* Variables and functions */
 struct net_device* stub1 (int /*<<< orphan*/ *,char const*,unsigned char,int) ; 

__attribute__((used)) static inline struct net_device *
rdev_add_virtual_intf_deprecated(struct cfg802154_registered_device *rdev,
				 const char *name,
				 unsigned char name_assign_type,
				 int type)
{
	return rdev->ops->add_virtual_intf_deprecated(&rdev->wpan_phy, name,
						      name_assign_type, type);
}
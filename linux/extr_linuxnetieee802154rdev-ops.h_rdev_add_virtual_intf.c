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
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
typedef  enum nl802154_iftype { ____Placeholder_nl802154_iftype } nl802154_iftype ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int (* add_virtual_intf ) (int /*<<< orphan*/ *,char*,unsigned char,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,char*,unsigned char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_rdev_add_virtual_intf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
rdev_add_virtual_intf(struct cfg802154_registered_device *rdev, char *name,
		      unsigned char name_assign_type,
		      enum nl802154_iftype type, __le64 extended_addr)
{
	int ret;

	trace_802154_rdev_add_virtual_intf(&rdev->wpan_phy, name, type,
					   extended_addr);
	ret = rdev->ops->add_virtual_intf(&rdev->wpan_phy, name,
					  name_assign_type, type,
					  extended_addr);
	trace_802154_rdev_return_int(&rdev->wpan_phy, ret);
	return ret;
}
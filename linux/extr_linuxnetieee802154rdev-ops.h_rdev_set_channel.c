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
typedef  int /*<<< orphan*/  u8 ;
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_channel ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_802154_rdev_set_channel (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rdev_set_channel(struct cfg802154_registered_device *rdev, u8 page, u8 channel)
{
	int ret;

	trace_802154_rdev_set_channel(&rdev->wpan_phy, page, channel);
	ret = rdev->ops->set_channel(&rdev->wpan_phy, page, channel);
	trace_802154_rdev_return_int(&rdev->wpan_phy, ret);
	return ret;
}
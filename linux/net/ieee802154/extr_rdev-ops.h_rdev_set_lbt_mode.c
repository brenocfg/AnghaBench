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
struct wpan_dev {int dummy; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_lbt_mode ) (int /*<<< orphan*/ *,struct wpan_dev*,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wpan_dev*,int) ; 
 int /*<<< orphan*/  trace_802154_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_802154_rdev_set_lbt_mode (int /*<<< orphan*/ *,struct wpan_dev*,int) ; 

__attribute__((used)) static inline int
rdev_set_lbt_mode(struct cfg802154_registered_device *rdev,
		  struct wpan_dev *wpan_dev, bool mode)
{
	int ret;

	trace_802154_rdev_set_lbt_mode(&rdev->wpan_phy, wpan_dev, mode);
	ret = rdev->ops->set_lbt_mode(&rdev->wpan_phy, wpan_dev, mode);
	trace_802154_rdev_return_int(&rdev->wpan_phy, ret);
	return ret;
}
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
struct wpan_dev {int dummy; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_backoff_exponent ) (int /*<<< orphan*/ *,struct wpan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wpan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_802154_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_802154_rdev_set_backoff_exponent (int /*<<< orphan*/ *,struct wpan_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rdev_set_backoff_exponent(struct cfg802154_registered_device *rdev,
			  struct wpan_dev *wpan_dev, u8 min_be, u8 max_be)
{
	int ret;

	trace_802154_rdev_set_backoff_exponent(&rdev->wpan_phy, wpan_dev,
					       min_be, max_be);
	ret = rdev->ops->set_backoff_exponent(&rdev->wpan_phy, wpan_dev,
					      min_be, max_be);
	trace_802154_rdev_return_int(&rdev->wpan_phy, ret);
	return ret;
}
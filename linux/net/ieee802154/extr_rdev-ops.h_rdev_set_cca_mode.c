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
struct wpan_phy_cca {int dummy; } ;
struct cfg802154_registered_device {int /*<<< orphan*/  wpan_phy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_cca_mode ) (int /*<<< orphan*/ *,struct wpan_phy_cca const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct wpan_phy_cca const*) ; 
 int /*<<< orphan*/  trace_802154_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_802154_rdev_set_cca_mode (int /*<<< orphan*/ *,struct wpan_phy_cca const*) ; 

__attribute__((used)) static inline int
rdev_set_cca_mode(struct cfg802154_registered_device *rdev,
		  const struct wpan_phy_cca *cca)
{
	int ret;

	trace_802154_rdev_set_cca_mode(&rdev->wpan_phy, cca);
	ret = rdev->ops->set_cca_mode(&rdev->wpan_phy, cca);
	trace_802154_rdev_return_int(&rdev->wpan_phy, ret);
	return ret;
}
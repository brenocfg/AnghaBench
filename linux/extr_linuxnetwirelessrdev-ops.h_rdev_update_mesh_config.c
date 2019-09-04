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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mesh_config {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* update_mesh_config ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,struct mesh_config const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,struct mesh_config const*) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_update_mesh_config (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/ ,struct mesh_config const*) ; 

__attribute__((used)) static inline int
rdev_update_mesh_config(struct cfg80211_registered_device *rdev,
			struct net_device *dev, u32 mask,
			const struct mesh_config *nconf)
{
	int ret;
	trace_rdev_update_mesh_config(&rdev->wiphy, dev, mask, nconf);
	ret = rdev->ops->update_mesh_config(&rdev->wiphy, dev, mask, nconf);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}
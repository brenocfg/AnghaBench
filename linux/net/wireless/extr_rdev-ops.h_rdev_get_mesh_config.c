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
struct mesh_config {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_mesh_config ) (int /*<<< orphan*/ *,struct net_device*,struct mesh_config*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,struct mesh_config*) ; 
 int /*<<< orphan*/  trace_rdev_get_mesh_config (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  trace_rdev_return_int_mesh_config (int /*<<< orphan*/ *,int,struct mesh_config*) ; 

__attribute__((used)) static inline int
rdev_get_mesh_config(struct cfg80211_registered_device *rdev,
		     struct net_device *dev, struct mesh_config *conf)
{
	int ret;
	trace_rdev_get_mesh_config(&rdev->wiphy, dev);
	ret = rdev->ops->get_mesh_config(&rdev->wiphy, dev, conf);
	trace_rdev_return_int_mesh_config(&rdev->wiphy, ret, conf);
	return ret;
}
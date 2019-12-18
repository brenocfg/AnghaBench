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
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* probe_mesh_link ) (int /*<<< orphan*/ *,struct net_device*,void const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,void const*,size_t) ; 
 int /*<<< orphan*/  trace_rdev_probe_mesh_link (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
rdev_probe_mesh_link(struct cfg80211_registered_device *rdev,
		     struct net_device *dev, const u8 *dest,
		     const void *buf, size_t len)
{
	int ret;

	trace_rdev_probe_mesh_link(&rdev->wiphy, dev, dest, buf, len);
	ret = rdev->ops->probe_mesh_link(&rdev->wiphy, dev, buf, len);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}
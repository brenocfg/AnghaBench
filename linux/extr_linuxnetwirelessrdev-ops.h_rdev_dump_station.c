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
struct station_info {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* dump_station ) (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *,struct station_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *,struct station_info*) ; 
 int /*<<< orphan*/  trace_rdev_dump_station (int /*<<< orphan*/ *,struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_return_int_station_info (int /*<<< orphan*/ *,int,struct station_info*) ; 

__attribute__((used)) static inline int rdev_dump_station(struct cfg80211_registered_device *rdev,
				    struct net_device *dev, int idx, u8 *mac,
				    struct station_info *sinfo)
{
	int ret;
	trace_rdev_dump_station(&rdev->wiphy, dev, idx, mac);
	ret = rdev->ops->dump_station(&rdev->wiphy, dev, idx, mac, sinfo);
	trace_rdev_return_int_station_info(&rdev->wiphy, ret, sinfo);
	return ret;
}
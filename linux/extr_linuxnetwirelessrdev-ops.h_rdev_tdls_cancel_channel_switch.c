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
struct TYPE_2__ {int /*<<< orphan*/  (* tdls_cancel_channel_switch ) (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  trace_rdev_return_void (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rdev_tdls_cancel_channel_switch (int /*<<< orphan*/ *,struct net_device*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void
rdev_tdls_cancel_channel_switch(struct cfg80211_registered_device *rdev,
				struct net_device *dev, const u8 *addr)
{
	trace_rdev_tdls_cancel_channel_switch(&rdev->wiphy, dev, addr);
	rdev->ops->tdls_cancel_channel_switch(&rdev->wiphy, dev, addr);
	trace_rdev_return_void(&rdev->wiphy);
}
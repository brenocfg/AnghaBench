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
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int (* tx_control_port ) (int /*<<< orphan*/ *,struct net_device*,void const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int const) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct net_device*,void const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  trace_rdev_return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace_rdev_tx_control_port (int /*<<< orphan*/ *,struct net_device*,void const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static inline int rdev_tx_control_port(struct cfg80211_registered_device *rdev,
				       struct net_device *dev,
				       const void *buf, size_t len,
				       const u8 *dest, __be16 proto,
				       const bool noencrypt)
{
	int ret;
	trace_rdev_tx_control_port(&rdev->wiphy, dev, buf, len,
				   dest, proto, noencrypt);
	ret = rdev->ops->tx_control_port(&rdev->wiphy, dev, buf, len,
					 dest, proto, noencrypt);
	trace_rdev_return_int(&rdev->wiphy, ret);
	return ret;
}
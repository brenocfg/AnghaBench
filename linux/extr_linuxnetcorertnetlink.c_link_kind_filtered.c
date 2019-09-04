#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtnl_link_ops {int dummy; } ;
struct net_device {struct rtnl_link_ops const* rtnl_link_ops; } ;

/* Variables and functions */

__attribute__((used)) static bool link_kind_filtered(const struct net_device *dev,
			       const struct rtnl_link_ops *kind_ops)
{
	if (kind_ops && dev->rtnl_link_ops != kind_ops)
		return true;

	return false;
}
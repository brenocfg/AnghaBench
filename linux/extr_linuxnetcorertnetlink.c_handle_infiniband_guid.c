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
struct net_device_ops {int (* ndo_set_vf_guid ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct ifla_vf_guid {int /*<<< orphan*/  guid; int /*<<< orphan*/  vf; } ;

/* Variables and functions */
 int stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_infiniband_guid(struct net_device *dev, struct ifla_vf_guid *ivt,
				  int guid_type)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	return ops->ndo_set_vf_guid(dev, ivt->vf, ivt->guid, guid_type);
}
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
struct net_device {scalar_t__ type; } ;
struct ifla_vf_guid {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_INFINIBAND ; 
 int EOPNOTSUPP ; 
 int handle_infiniband_guid (struct net_device*,struct ifla_vf_guid*,int) ; 

__attribute__((used)) static int handle_vf_guid(struct net_device *dev, struct ifla_vf_guid *ivt, int guid_type)
{
	if (dev->type != ARPHRD_INFINIBAND)
		return -EOPNOTSUPP;

	return handle_infiniband_guid(dev, ivt, guid_type);
}
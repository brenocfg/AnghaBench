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
struct vport {struct datapath* dp; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct datapath {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 struct vport* ovs_internal_dev_get_vport (struct net_device*) ; 

__attribute__((used)) static inline struct datapath *get_dp_rcu(struct net *net, int dp_ifindex)
{
	struct net_device *dev = dev_get_by_index_rcu(net, dp_ifindex);

	if (dev) {
		struct vport *vport = ovs_internal_dev_get_vport(dev);

		if (vport)
			return vport->dp;
	}

	return NULL;
}
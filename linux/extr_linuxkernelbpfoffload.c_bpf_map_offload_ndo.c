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
struct netdev_bpf {int command; struct bpf_offloaded_map* offmap; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
struct bpf_offloaded_map {struct net_device* netdev; } ;
typedef  enum bpf_netdev_command { ____Placeholder_bpf_netdev_command } bpf_netdev_command ;
struct TYPE_2__ {int (* ndo_bpf ) (struct net_device*,struct netdev_bpf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int stub1 (struct net_device*,struct netdev_bpf*) ; 

__attribute__((used)) static int bpf_map_offload_ndo(struct bpf_offloaded_map *offmap,
			       enum bpf_netdev_command cmd)
{
	struct netdev_bpf data = {};
	struct net_device *netdev;

	ASSERT_RTNL();

	data.command = cmd;
	data.offmap = offmap;
	/* Caller must make sure netdev is valid */
	netdev = offmap->netdev;

	return netdev->netdev_ops->ndo_bpf(netdev, &data);
}
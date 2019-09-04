#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netdev_bpf {int command; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
struct bpf_prog_offload {struct net_device* netdev; } ;
struct bpf_prog {TYPE_1__* aux; } ;
typedef  enum bpf_netdev_command { ____Placeholder_bpf_netdev_command } bpf_netdev_command ;
struct TYPE_4__ {int (* ndo_bpf ) (struct net_device*,struct netdev_bpf*) ;} ;
struct TYPE_3__ {struct bpf_prog_offload* offload; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENODEV ; 
 int stub1 (struct net_device*,struct netdev_bpf*) ; 

__attribute__((used)) static int __bpf_offload_ndo(struct bpf_prog *prog, enum bpf_netdev_command cmd,
			     struct netdev_bpf *data)
{
	struct bpf_prog_offload *offload = prog->aux->offload;
	struct net_device *netdev;

	ASSERT_RTNL();

	if (!offload)
		return -ENODEV;
	netdev = offload->netdev;

	data->command = cmd;

	return netdev->netdev_ops->ndo_bpf(netdev, data);
}
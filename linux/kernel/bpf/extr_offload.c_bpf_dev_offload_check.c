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
struct net_device {TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  ndo_bpf; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 

__attribute__((used)) static int bpf_dev_offload_check(struct net_device *netdev)
{
	if (!netdev)
		return -EINVAL;
	if (!netdev->netdev_ops->ndo_bpf)
		return -EOPNOTSUPP;
	return 0;
}
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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  queue_id; } ;
struct netdev_bpf {TYPE_1__ xsk; int /*<<< orphan*/  command; } ;
struct net_device {TYPE_2__* netdev_ops; } ;
typedef  int /*<<< orphan*/  bpf ;
struct TYPE_4__ {scalar_t__ (* ndo_bpf ) (struct net_device*,struct netdev_bpf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  XDP_QUERY_XSK_UMEM ; 
 int /*<<< orphan*/  memset (struct netdev_bpf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct net_device*,struct netdev_bpf*) ; 

int xdp_umem_query(struct net_device *dev, u16 queue_id)
{
	struct netdev_bpf bpf;

	ASSERT_RTNL();

	memset(&bpf, 0, sizeof(bpf));
	bpf.command = XDP_QUERY_XSK_UMEM;
	bpf.xsk.queue_id = queue_id;

	if (!dev->netdev_ops->ndo_bpf)
		return 0;
	return dev->netdev_ops->ndo_bpf(dev, &bpf) ?: !!bpf.xsk.umem;
}
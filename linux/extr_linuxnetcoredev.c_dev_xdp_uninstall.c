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
typedef  int /*<<< orphan*/  xdp ;
struct netdev_bpf {int /*<<< orphan*/  prog_flags; scalar_t__ prog_id; int /*<<< orphan*/  command; } ;
struct net_device {TYPE_1__* netdev_ops; } ;
typedef  int /*<<< orphan*/  (* bpf_op_t ) (struct net_device*,struct netdev_bpf*) ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_bpf ) (struct net_device*,struct netdev_bpf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDP_QUERY_PROG ; 
 int /*<<< orphan*/  XDP_QUERY_PROG_HW ; 
 int /*<<< orphan*/  dev_xdp_install (struct net_device*,int /*<<< orphan*/  (*) (struct net_device*,struct netdev_bpf*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_xdp_install (struct net_device*,struct netdev_bpf*) ; 
 int /*<<< orphan*/  memset (struct netdev_bpf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dev_xdp_uninstall(struct net_device *dev)
{
	struct netdev_bpf xdp;
	bpf_op_t ndo_bpf;

	/* Remove generic XDP */
	WARN_ON(dev_xdp_install(dev, generic_xdp_install, NULL, 0, NULL));

	/* Remove from the driver */
	ndo_bpf = dev->netdev_ops->ndo_bpf;
	if (!ndo_bpf)
		return;

	memset(&xdp, 0, sizeof(xdp));
	xdp.command = XDP_QUERY_PROG;
	WARN_ON(ndo_bpf(dev, &xdp));
	if (xdp.prog_id)
		WARN_ON(dev_xdp_install(dev, ndo_bpf, NULL, xdp.prog_flags,
					NULL));

	/* Remove HW offload */
	memset(&xdp, 0, sizeof(xdp));
	xdp.command = XDP_QUERY_PROG_HW;
	if (!ndo_bpf(dev, &xdp) && xdp.prog_id)
		WARN_ON(dev_xdp_install(dev, ndo_bpf, NULL, xdp.prog_flags,
					NULL));
}
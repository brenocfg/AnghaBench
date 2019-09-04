#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int prog; } ;
struct TYPE_4__ {int prog; } ;
struct netdevsim {int bpf_offloaded; TYPE_3__* sdev; int /*<<< orphan*/  netdev; TYPE_2__ xdp_hw; TYPE_1__ xdp; } ;
struct TYPE_6__ {int refcnt; int /*<<< orphan*/  bpf_dev; int /*<<< orphan*/  bpf_bound_maps; int /*<<< orphan*/  bpf_bound_progs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bpf_offload_dev_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_offload_dev_netdev_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void nsim_bpf_uninit(struct netdevsim *ns)
{
	WARN_ON(ns->xdp.prog);
	WARN_ON(ns->xdp_hw.prog);
	WARN_ON(ns->bpf_offloaded);
	bpf_offload_dev_netdev_unregister(ns->sdev->bpf_dev, ns->netdev);

	if (ns->sdev->refcnt == 1) {
		WARN_ON(!list_empty(&ns->sdev->bpf_bound_progs));
		WARN_ON(!list_empty(&ns->sdev->bpf_bound_maps));
		bpf_offload_dev_destroy(ns->sdev->bpf_dev);
	}
}
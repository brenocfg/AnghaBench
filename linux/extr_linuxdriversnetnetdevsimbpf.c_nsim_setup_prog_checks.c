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
struct netdevsim {TYPE_3__* netdev; } ;
struct netdev_bpf {int /*<<< orphan*/  extack; TYPE_2__* prog; } ;
struct TYPE_6__ {scalar_t__ mtu; } ;
struct TYPE_5__ {TYPE_1__* aux; } ;
struct TYPE_4__ {scalar_t__ offload; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NSIM_EA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NSIM_XDP_MAX_MTU ; 

__attribute__((used)) static int nsim_setup_prog_checks(struct netdevsim *ns, struct netdev_bpf *bpf)
{
	if (bpf->prog && bpf->prog->aux->offload) {
		NSIM_EA(bpf->extack, "attempt to load offloaded prog to drv");
		return -EINVAL;
	}
	if (ns->netdev->mtu > NSIM_XDP_MAX_MTU) {
		NSIM_EA(bpf->extack, "MTU too large w/ XDP enabled");
		return -EINVAL;
	}
	return 0;
}
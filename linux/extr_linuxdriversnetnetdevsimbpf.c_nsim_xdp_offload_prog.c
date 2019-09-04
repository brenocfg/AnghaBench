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
struct netdevsim {scalar_t__ bpf_offloaded; } ;
struct netdev_bpf {scalar_t__ prog; int /*<<< orphan*/  extack; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NSIM_EA (int /*<<< orphan*/ ,char*) ; 
 int nsim_bpf_offload (struct netdevsim*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_xdp_offload_active (struct netdevsim*) ; 

__attribute__((used)) static int nsim_xdp_offload_prog(struct netdevsim *ns, struct netdev_bpf *bpf)
{
	if (!nsim_xdp_offload_active(ns) && !bpf->prog)
		return 0;
	if (!nsim_xdp_offload_active(ns) && bpf->prog && ns->bpf_offloaded) {
		NSIM_EA(bpf->extack, "TC program is already loaded");
		return -EBUSY;
	}

	return nsim_bpf_offload(ns, bpf->prog, nsim_xdp_offload_active(ns));
}
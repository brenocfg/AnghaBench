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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  nsim_xdp_offload_active (struct netdevsim*) ; 

int nsim_bpf_disable_tc(struct netdevsim *ns)
{
	if (ns->bpf_offloaded && !nsim_xdp_offload_active(ns))
		return -EBUSY;
	return 0;
}
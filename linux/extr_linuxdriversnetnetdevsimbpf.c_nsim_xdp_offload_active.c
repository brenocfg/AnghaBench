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
struct TYPE_2__ {int prog; } ;
struct netdevsim {TYPE_1__ xdp_hw; } ;

/* Variables and functions */

__attribute__((used)) static bool nsim_xdp_offload_active(struct netdevsim *ns)
{
	return ns->xdp_hw.prog;
}
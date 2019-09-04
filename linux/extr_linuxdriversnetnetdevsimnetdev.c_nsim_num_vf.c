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
struct netdevsim {int num_vfs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct netdevsim* to_nsim (struct device*) ; 

__attribute__((used)) static int nsim_num_vf(struct device *dev)
{
	struct netdevsim *ns = to_nsim(dev);

	return ns->num_vfs;
}
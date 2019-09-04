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
struct nsim_vf_config {int dummy; } ;
struct netdevsim {unsigned int num_vfs; int /*<<< orphan*/  vfconfigs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsim_vfs_enable(struct netdevsim *ns, unsigned int num_vfs)
{
	ns->vfconfigs = kcalloc(num_vfs, sizeof(struct nsim_vf_config),
				GFP_KERNEL);
	if (!ns->vfconfigs)
		return -ENOMEM;
	ns->num_vfs = num_vfs;

	return 0;
}
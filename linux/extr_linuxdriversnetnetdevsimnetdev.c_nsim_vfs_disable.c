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
struct netdevsim {scalar_t__ num_vfs; int /*<<< orphan*/ * vfconfigs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nsim_vfs_disable(struct netdevsim *ns)
{
	kfree(ns->vfconfigs);
	ns->vfconfigs = NULL;
	ns->num_vfs = 0;
}
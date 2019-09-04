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
struct proc_dir_entry {int /*<<< orphan*/ * proc_dops; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_net_dentry_ops ; 

__attribute__((used)) static void pde_force_lookup(struct proc_dir_entry *pde)
{
	/* /proc/net/ entries can be changed under us by setns(CLONE_NEWNET) */
	pde->proc_dops = &proc_net_dentry_ops;
}
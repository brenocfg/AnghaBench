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
struct dentry {int /*<<< orphan*/ * d_fsdata; int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  mntns_operations ; 
 int /*<<< orphan*/  ns_dentry_operations ; 

__attribute__((used)) static bool is_mnt_ns_file(struct dentry *dentry)
{
	/* Is this a proxy for a mount namespace? */
	return dentry->d_op == &ns_dentry_operations &&
	       dentry->d_fsdata == &mntns_operations;
}
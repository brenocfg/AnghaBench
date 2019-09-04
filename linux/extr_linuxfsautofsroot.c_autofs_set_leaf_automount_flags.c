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
struct dentry {struct dentry* d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  managed_dentry_clear_managed (struct dentry*) ; 
 int /*<<< orphan*/  managed_dentry_set_managed (struct dentry*) ; 

__attribute__((used)) static void autofs_set_leaf_automount_flags(struct dentry *dentry)
{
	struct dentry *parent;

	/* root and dentrys in the root are already handled */
	if (IS_ROOT(dentry->d_parent))
		return;

	managed_dentry_set_managed(dentry);

	parent = dentry->d_parent;
	/* only consider parents below dentrys in the root */
	if (IS_ROOT(parent->d_parent))
		return;
	managed_dentry_clear_managed(parent);
}
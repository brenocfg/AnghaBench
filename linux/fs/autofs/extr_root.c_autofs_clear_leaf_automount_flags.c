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
struct list_head {int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; } ;
struct dentry {int /*<<< orphan*/  d_subdirs; struct list_head d_child; struct dentry* d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  managed_dentry_clear_managed (struct dentry*) ; 
 int /*<<< orphan*/  managed_dentry_set_managed (struct dentry*) ; 

__attribute__((used)) static void autofs_clear_leaf_automount_flags(struct dentry *dentry)
{
	struct list_head *d_child;
	struct dentry *parent;

	/* flags for dentrys in the root are handled elsewhere */
	if (IS_ROOT(dentry->d_parent))
		return;

	managed_dentry_clear_managed(dentry);

	parent = dentry->d_parent;
	/* only consider parents below dentrys in the root */
	if (IS_ROOT(parent->d_parent))
		return;
	d_child = &dentry->d_child;
	/* Set parent managed if it's becoming empty */
	if (d_child->next == &parent->d_subdirs &&
	    d_child->prev == &parent->d_subdirs)
		managed_dentry_set_managed(parent);
}
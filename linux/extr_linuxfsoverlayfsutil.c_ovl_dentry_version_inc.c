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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 
 scalar_t__ OVL_TYPE_MERGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 
 int /*<<< orphan*/  ovl_path_type (struct dentry*) ; 

__attribute__((used)) static void ovl_dentry_version_inc(struct dentry *dentry, bool impurity)
{
	struct inode *inode = d_inode(dentry);

	WARN_ON(!inode_is_locked(inode));
	/*
	 * Version is used by readdir code to keep cache consistent.  For merge
	 * dirs all changes need to be noted.  For non-merge dirs, cache only
	 * contains impure (ones which have been copied up and have origins)
	 * entries, so only need to note changes to impure entries.
	 */
	if (OVL_TYPE_MERGE(ovl_path_type(dentry)) || impurity)
		OVL_I(inode)->version++;
}
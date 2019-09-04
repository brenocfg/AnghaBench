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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_1__* OVL_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_is_locked (struct inode*) ; 

u64 ovl_dentry_version_get(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);

	WARN_ON(!inode_is_locked(inode));
	return OVL_I(inode)->version;
}
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
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int EACCES ; 
 TYPE_1__* NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int nfs_setattr (struct dentry*,struct iattr*) ; 

__attribute__((used)) static int
nfs_namespace_setattr(struct dentry *dentry, struct iattr *attr)
{
	if (NFS_FH(d_inode(dentry))->size != 0)
		return nfs_setattr(dentry, attr);
	return -EACCES;
}
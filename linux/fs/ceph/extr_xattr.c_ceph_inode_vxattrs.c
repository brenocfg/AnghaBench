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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct ceph_vxattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct ceph_vxattr* ceph_dir_vxattrs ; 
 struct ceph_vxattr* ceph_file_vxattrs ; 

__attribute__((used)) static struct ceph_vxattr *ceph_inode_vxattrs(struct inode *inode)
{
	if (S_ISDIR(inode->i_mode))
		return ceph_dir_vxattrs;
	else if (S_ISREG(inode->i_mode))
		return ceph_file_vxattrs;
	return NULL;
}
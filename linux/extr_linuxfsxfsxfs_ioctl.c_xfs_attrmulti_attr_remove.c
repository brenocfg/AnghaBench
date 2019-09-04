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
typedef  int /*<<< orphan*/  uint32_t ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  XFS_I (struct inode*) ; 
 int xfs_attr_remove (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_forget_acl (struct inode*,unsigned char*,int /*<<< orphan*/ ) ; 

int
xfs_attrmulti_attr_remove(
	struct inode		*inode,
	unsigned char		*name,
	uint32_t		flags)
{
	int			error;

	if (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		return -EPERM;
	error = xfs_attr_remove(XFS_I(inode), name, flags);
	if (!error)
		xfs_forget_acl(inode, name, flags);
	return error;
}
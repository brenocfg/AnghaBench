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
typedef  scalar_t__ umode_t ;
struct inode {scalar_t__ i_mode; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_ctime; scalar_t__ ia_mode; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MODE ; 
 int /*<<< orphan*/  XFS_ATTR_NOACL ; 
 int /*<<< orphan*/  XFS_I (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int xfs_setattr_nonsize (int /*<<< orphan*/ ,struct iattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_set_mode(struct inode *inode, umode_t mode)
{
	int error = 0;

	if (mode != inode->i_mode) {
		struct iattr iattr;

		iattr.ia_valid = ATTR_MODE | ATTR_CTIME;
		iattr.ia_mode = mode;
		iattr.ia_ctime = current_time(inode);

		error = xfs_setattr_nonsize(XFS_I(inode), &iattr, XFS_ATTR_NOACL);
	}

	return error;
}
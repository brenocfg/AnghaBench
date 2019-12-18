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
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FSETID ; 
 int /*<<< orphan*/  S_ISGID ; 
 int /*<<< orphan*/  capable_wrt_inode_uidgid (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_group_p (int /*<<< orphan*/ ) ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 

int posix_acl_update_mode(struct inode *inode, umode_t *mode_p,
			  struct posix_acl **acl)
{
	umode_t mode = inode->i_mode;
	int error;

	error = posix_acl_equiv_mode(*acl, &mode);
	if (error < 0)
		return error;
	if (error == 0)
		*acl = NULL;
	if (!in_group_p(inode->i_gid) &&
	    !capable_wrt_inode_uidgid(inode, CAP_FSETID))
		mode &= ~S_ISGID;
	*mode_p = mode;
	return 0;
}
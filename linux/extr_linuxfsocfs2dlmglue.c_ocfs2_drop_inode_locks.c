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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_rw_lockres; int /*<<< orphan*/  ip_inode_lockres; int /*<<< orphan*/  ip_open_lockres; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_drop_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ocfs2_drop_inode_locks(struct inode *inode)
{
	int status, err;

	/* No need to call ocfs2_mark_lockres_freeing here -
	 * ocfs2_clear_inode has done it for us. */

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_open_lockres);
	if (err < 0)
		mlog_errno(err);

	status = err;

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_inode_lockres);
	if (err < 0)
		mlog_errno(err);
	if (err < 0 && !status)
		status = err;

	err = ocfs2_drop_lock(OCFS2_SB(inode->i_sb),
			      &OCFS2_I(inode)->ip_rw_lockres);
	if (err < 0)
		mlog_errno(err);
	if (err < 0 && !status)
		status = err;

	return status;
}
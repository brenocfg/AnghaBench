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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static struct inode *ocfs2_get_init_inode(struct inode *dir, umode_t mode)
{
	struct inode *inode;
	int status;

	inode = new_inode(dir->i_sb);
	if (!inode) {
		mlog(ML_ERROR, "new_inode failed!\n");
		return ERR_PTR(-ENOMEM);
	}

	/* populate as many fields early on as possible - many of
	 * these are used by the support functions here and in
	 * callers. */
	if (S_ISDIR(mode))
		set_nlink(inode, 2);
	inode_init_owner(inode, dir, mode);
	status = dquot_initialize(inode);
	if (status)
		return ERR_PTR(status);

	return inode;
}
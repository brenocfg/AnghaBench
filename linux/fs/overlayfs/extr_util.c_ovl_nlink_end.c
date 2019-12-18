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
struct inode {scalar_t__ i_nlink; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_INDEX ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ovl_cleanup_index (struct dentry*) ; 
 int /*<<< orphan*/  ovl_inode_unlock (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

void ovl_nlink_end(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);

	if (ovl_test_flag(OVL_INDEX, inode) && inode->i_nlink == 0) {
		const struct cred *old_cred;

		old_cred = ovl_override_creds(dentry->d_sb);
		ovl_cleanup_index(dentry);
		revert_creds(old_cred);
	}

	ovl_inode_unlock(inode);
}
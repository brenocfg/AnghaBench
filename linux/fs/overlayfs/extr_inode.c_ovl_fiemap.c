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
struct inode {TYPE_1__* i_op; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct fiemap_extent_info {int fi_flags; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {int (* fiemap ) (struct inode*,struct fiemap_extent_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FIEMAP_FLAG_SYNC ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 struct inode* ovl_inode_real (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int stub1 (struct inode*,struct fiemap_extent_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_fiemap(struct inode *inode, struct fiemap_extent_info *fieinfo,
		      u64 start, u64 len)
{
	int err;
	struct inode *realinode = ovl_inode_real(inode);
	const struct cred *old_cred;

	if (!realinode->i_op->fiemap)
		return -EOPNOTSUPP;

	old_cred = ovl_override_creds(inode->i_sb);

	if (fieinfo->fi_flags & FIEMAP_FLAG_SYNC)
		filemap_write_and_wait(realinode->i_mapping);

	err = realinode->i_op->fiemap(realinode, fieinfo, start, len);
	revert_creds(old_cred);

	return err;
}
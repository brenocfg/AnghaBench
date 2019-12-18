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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int OCFS2_BH_READAHEAD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_check_dir_trailer (struct inode*,struct buffer_head*) ; 
 int ocfs2_read_virt_blocks (struct inode*,int /*<<< orphan*/ ,int,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_supports_dir_trailer (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_validate_dir_block ; 

__attribute__((used)) static int ocfs2_read_dir_block(struct inode *inode, u64 v_block,
				struct buffer_head **bh, int flags)
{
	int rc = 0;
	struct buffer_head *tmp = *bh;

	rc = ocfs2_read_virt_blocks(inode, v_block, 1, &tmp, flags,
				    ocfs2_validate_dir_block);
	if (rc) {
		mlog_errno(rc);
		goto out;
	}

	if (!(flags & OCFS2_BH_READAHEAD) &&
	    ocfs2_supports_dir_trailer(inode)) {
		rc = ocfs2_check_dir_trailer(inode, tmp);
		if (rc) {
			if (!*bh)
				brelse(tmp);
			mlog_errno(rc);
			goto out;
		}
	}

	/* If ocfs2_read_virt_blocks() got us a new bh, pass it up. */
	if (!*bh)
		*bh = tmp;

out:
	return rc ? -EIO : 0;
}
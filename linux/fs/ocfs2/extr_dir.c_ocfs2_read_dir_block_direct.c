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
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_check_dir_trailer (struct inode*,struct buffer_head*) ; 
 int ocfs2_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_supports_dir_trailer (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_validate_dir_block ; 

__attribute__((used)) static int ocfs2_read_dir_block_direct(struct inode *dir, u64 phys,
				       struct buffer_head **bh)
{
	int ret;
	struct buffer_head *tmp = *bh;

	ret = ocfs2_read_block(INODE_CACHE(dir), phys, &tmp,
			       ocfs2_validate_dir_block);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (ocfs2_supports_dir_trailer(dir)) {
		ret = ocfs2_check_dir_trailer(dir, tmp);
		if (ret) {
			if (!*bh)
				brelse(tmp);
			mlog_errno(ret);
			goto out;
		}
	}

	if (!ret && !*bh)
		*bh = tmp;
out:
	return ret;
}
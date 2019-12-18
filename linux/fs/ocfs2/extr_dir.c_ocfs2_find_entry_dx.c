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
struct ocfs2_dx_root_block {int dummy; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_dx_root_bh; } ;
struct ocfs2_dinode {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dx_dir_search (char const*,int,struct inode*,struct ocfs2_dx_root_block*,struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_read_dx_root (struct inode*,struct ocfs2_dinode*,struct buffer_head**) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_find_entry_dx(const char *name, int namelen,
			       struct inode *dir,
			       struct ocfs2_dir_lookup_result *lookup)
{
	int ret;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	struct buffer_head *dx_root_bh = NULL;
	struct ocfs2_dx_root_block *dx_root;

	ret = ocfs2_read_inode_block(dir, &di_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;

	ret = ocfs2_read_dx_root(dir, di, &dx_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	dx_root = (struct ocfs2_dx_root_block *) dx_root_bh->b_data;

	ret = ocfs2_dx_dir_search(name, namelen, dir, dx_root, lookup);
	if (ret) {
		if (ret != -ENOENT)
			mlog_errno(ret);
		goto out;
	}

	lookup->dl_dx_root_bh = dx_root_bh;
	dx_root_bh = NULL;
out:
	brelse(di_bh);
	brelse(dx_root_bh);
	return ret;
}
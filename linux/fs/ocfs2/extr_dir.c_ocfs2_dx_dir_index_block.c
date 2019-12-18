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
typedef  scalar_t__ u32 ;
struct ocfs2_dx_hinfo {int dummy; } ;
struct ocfs2_dir_entry {int name_len; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  name; int /*<<< orphan*/  inode; } ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {char* b_data; int /*<<< orphan*/  b_blocknr; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_SB (TYPE_1__*) ; 
 int __ocfs2_dx_dir_leaf_insert (struct inode*,int /*<<< orphan*/ *,struct ocfs2_dx_hinfo*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_dx_dir_hash_idx (int /*<<< orphan*/ ,struct ocfs2_dx_hinfo*) ; 
 int /*<<< orphan*/  ocfs2_dx_dir_name_hash (struct inode*,int /*<<< orphan*/ ,int,struct ocfs2_dx_hinfo*) ; 

__attribute__((used)) static int ocfs2_dx_dir_index_block(struct inode *dir,
				    handle_t *handle,
				    struct buffer_head **dx_leaves,
				    int num_dx_leaves,
				    u32 *num_dx_entries,
				    struct buffer_head *dirent_bh)
{
	int ret = 0, namelen, i;
	char *de_buf, *limit;
	struct ocfs2_dir_entry *de;
	struct buffer_head *dx_leaf_bh;
	struct ocfs2_dx_hinfo hinfo;
	u64 dirent_blk = dirent_bh->b_blocknr;

	de_buf = dirent_bh->b_data;
	limit = de_buf + dir->i_sb->s_blocksize;

	while (de_buf < limit) {
		de = (struct ocfs2_dir_entry *)de_buf;

		namelen = de->name_len;
		if (!namelen || !de->inode)
			goto inc;

		ocfs2_dx_dir_name_hash(dir, de->name, namelen, &hinfo);

		i = ocfs2_dx_dir_hash_idx(OCFS2_SB(dir->i_sb), &hinfo);
		dx_leaf_bh = dx_leaves[i];

		ret = __ocfs2_dx_dir_leaf_insert(dir, handle, &hinfo,
						 dirent_blk, dx_leaf_bh);
		if (ret) {
			mlog_errno(ret);
			goto out;
		}

		*num_dx_entries = *num_dx_entries + 1;

inc:
		de_buf += le16_to_cpu(de->rec_len);
	}

out:
	return ret;
}
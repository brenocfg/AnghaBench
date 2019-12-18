#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {TYPE_1__* sb; } ;
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; } ;
struct ocfs2_dir_block_trailer {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_blocks; TYPE_2__* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_3__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned int ocfs2_dir_trailer_blk_off (TYPE_2__*) ; 
 int ocfs2_do_extend_dir (TYPE_1__*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct ocfs2_alloc_context*,int /*<<< orphan*/ *,struct buffer_head**) ; 
 struct ocfs2_dir_entry* ocfs2_fill_initial_dirents (struct inode*,struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_init_dir_trailer (struct inode*,struct buffer_head*,int) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ocfs2_new_dir_wants_trailer (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

__attribute__((used)) static int ocfs2_fill_new_dir_el(struct ocfs2_super *osb,
				 handle_t *handle,
				 struct inode *parent,
				 struct inode *inode,
				 struct buffer_head *fe_bh,
				 struct ocfs2_alloc_context *data_ac,
				 struct buffer_head **ret_new_bh)
{
	int status;
	unsigned int size = osb->sb->s_blocksize;
	struct buffer_head *new_bh = NULL;
	struct ocfs2_dir_entry *de;

	if (ocfs2_new_dir_wants_trailer(inode))
		size = ocfs2_dir_trailer_blk_off(parent->i_sb);

	status = ocfs2_do_extend_dir(osb->sb, handle, inode, fe_bh,
				     data_ac, NULL, &new_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), new_bh);

	status = ocfs2_journal_access_db(handle, INODE_CACHE(inode), new_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	memset(new_bh->b_data, 0, osb->sb->s_blocksize);

	de = ocfs2_fill_initial_dirents(inode, parent, new_bh->b_data, size);
	if (ocfs2_new_dir_wants_trailer(inode)) {
		int size = le16_to_cpu(de->rec_len);

		/*
		 * Figure out the size of the hole left over after
		 * insertion of '.' and '..'. The trailer wants this
		 * information.
		 */
		size -= OCFS2_DIR_REC_LEN(2);
		size -= sizeof(struct ocfs2_dir_block_trailer);

		ocfs2_init_dir_trailer(inode, new_bh, size);
	}

	ocfs2_journal_dirty(handle, new_bh);

	i_size_write(inode, inode->i_sb->s_blocksize);
	set_nlink(inode, 2);
	inode->i_blocks = ocfs2_inode_sector_count(inode);
	status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = 0;
	if (ret_new_bh) {
		*ret_new_bh = new_bh;
		new_bh = NULL;
	}
bail:
	brelse(new_bh);

	return status;
}
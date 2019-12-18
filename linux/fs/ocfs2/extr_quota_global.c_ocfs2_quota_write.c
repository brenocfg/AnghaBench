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
struct super_block {size_t s_blocksize; size_t s_blocksize_bits; } ;
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_gqi_bh; struct inode* dqi_gqinode; } ;
struct mem_dqinfo {struct ocfs2_mem_dqinfo* dqi_priv; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; scalar_t__ b_data; } ;
typedef  int ssize_t ;
typedef  size_t sector_t ;
typedef  size_t loff_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int OCFS2_JOURNAL_ACCESS_CREATE ; 
 int OCFS2_JOURNAL_ACCESS_WRITE ; 
 int /*<<< orphan*/  OCFS2_QBLK_RESERVED_SPACE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/ * journal_current_handle () ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 size_t ocfs2_align_bytes_to_blocks (struct super_block*,size_t) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocfs2_journal_access_dq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int ocfs2_read_quota_phys_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_set_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_simple_size_update (struct inode*,int /*<<< orphan*/ ,size_t) ; 
 struct mem_dqinfo* sb_dqinfo (struct super_block*,int) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

ssize_t ocfs2_quota_write(struct super_block *sb, int type,
			  const char *data, size_t len, loff_t off)
{
	struct mem_dqinfo *info = sb_dqinfo(sb, type);
	struct ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	struct inode *gqinode = oinfo->dqi_gqinode;
	int offset = off & (sb->s_blocksize - 1);
	sector_t blk = off >> sb->s_blocksize_bits;
	int err = 0, new = 0, ja_type;
	struct buffer_head *bh = NULL;
	handle_t *handle = journal_current_handle();
	u64 pblock, pcount;

	if (!handle) {
		mlog(ML_ERROR, "Quota write (off=%llu, len=%llu) cancelled "
		     "because transaction was not started.\n",
		     (unsigned long long)off, (unsigned long long)len);
		return -EIO;
	}
	if (len > sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE - offset) {
		WARN_ON(1);
		len = sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE - offset;
	}

	if (i_size_read(gqinode) < off + len) {
		loff_t rounded_end =
				ocfs2_align_bytes_to_blocks(sb, off + len);

		/* Space is already allocated in ocfs2_acquire_dquot() */
		err = ocfs2_simple_size_update(gqinode,
					       oinfo->dqi_gqi_bh,
					       rounded_end);
		if (err < 0)
			goto out;
		new = 1;
	}
	err = ocfs2_extent_map_get_blocks(gqinode, blk, &pblock, &pcount, NULL);
	if (err) {
		mlog_errno(err);
		goto out;
	}
	/* Not rewriting whole block? */
	if ((offset || len < sb->s_blocksize - OCFS2_QBLK_RESERVED_SPACE) &&
	    !new) {
		err = ocfs2_read_quota_phys_block(gqinode, pblock, &bh);
		ja_type = OCFS2_JOURNAL_ACCESS_WRITE;
	} else {
		bh = sb_getblk(sb, pblock);
		if (!bh)
			err = -ENOMEM;
		ja_type = OCFS2_JOURNAL_ACCESS_CREATE;
	}
	if (err) {
		mlog_errno(err);
		goto out;
	}
	lock_buffer(bh);
	if (new)
		memset(bh->b_data, 0, sb->s_blocksize);
	memcpy(bh->b_data + offset, data, len);
	flush_dcache_page(bh->b_page);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);
	ocfs2_set_buffer_uptodate(INODE_CACHE(gqinode), bh);
	err = ocfs2_journal_access_dq(handle, INODE_CACHE(gqinode), bh,
				      ja_type);
	if (err < 0) {
		brelse(bh);
		goto out;
	}
	ocfs2_journal_dirty(handle, bh);
	brelse(bh);
out:
	if (err) {
		mlog_errno(err);
		return err;
	}
	inode_inc_iversion(gqinode);
	ocfs2_mark_inode_dirty(handle, gqinode, oinfo->dqi_gqi_bh);
	return len;
}
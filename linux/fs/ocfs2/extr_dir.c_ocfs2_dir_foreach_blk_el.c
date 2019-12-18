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
struct super_block {int s_blocksize; unsigned long s_blocksize_bits; } ;
struct ocfs2_dir_entry {int /*<<< orphan*/  rec_len; int /*<<< orphan*/  file_type; int /*<<< orphan*/  inode; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct inode {struct super_block* i_sb; } ;
struct dir_context {int pos; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_BH_READAHEAD ; 
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_ftype_to_dtype (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_eq_iversion (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,unsigned long) ; 
 scalar_t__ ocfs2_read_dir_block (struct inode*,unsigned long,struct buffer_head**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dir_foreach_blk_el(struct inode *inode,
				    u64 *f_version,
				    struct dir_context *ctx,
				    bool persist)
{
	unsigned long offset, blk, last_ra_blk = 0;
	int i;
	struct buffer_head * bh, * tmp;
	struct ocfs2_dir_entry * de;
	struct super_block * sb = inode->i_sb;
	unsigned int ra_sectors = 16;
	int stored = 0;

	bh = NULL;

	offset = ctx->pos & (sb->s_blocksize - 1);

	while (ctx->pos < i_size_read(inode)) {
		blk = ctx->pos >> sb->s_blocksize_bits;
		if (ocfs2_read_dir_block(inode, blk, &bh, 0)) {
			/* Skip the corrupt dirblock and keep trying */
			ctx->pos += sb->s_blocksize - offset;
			continue;
		}

		/* The idea here is to begin with 8k read-ahead and to stay
		 * 4k ahead of our current position.
		 *
		 * TODO: Use the pagecache for this. We just need to
		 * make sure it's cluster-safe... */
		if (!last_ra_blk
		    || (((last_ra_blk - blk) << 9) <= (ra_sectors / 2))) {
			for (i = ra_sectors >> (sb->s_blocksize_bits - 9);
			     i > 0; i--) {
				tmp = NULL;
				if (!ocfs2_read_dir_block(inode, ++blk, &tmp,
							  OCFS2_BH_READAHEAD))
					brelse(tmp);
			}
			last_ra_blk = blk;
			ra_sectors = 8;
		}

		/* If the dir block has changed since the last call to
		 * readdir(2), then we might be pointing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		if (!inode_eq_iversion(inode, *f_version)) {
			for (i = 0; i < sb->s_blocksize && i < offset; ) {
				de = (struct ocfs2_dir_entry *) (bh->b_data + i);
				/* It's too expensive to do a full
				 * dirent test each time round this
				 * loop, but we do have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				if (le16_to_cpu(de->rec_len) <
				    OCFS2_DIR_REC_LEN(1))
					break;
				i += le16_to_cpu(de->rec_len);
			}
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_blocksize - 1))
				| offset;
			*f_version = inode_query_iversion(inode);
		}

		while (ctx->pos < i_size_read(inode)
		       && offset < sb->s_blocksize) {
			de = (struct ocfs2_dir_entry *) (bh->b_data + offset);
			if (!ocfs2_check_dir_entry(inode, de, bh, offset)) {
				/* On error, skip the f_pos to the
				   next block. */
				ctx->pos = (ctx->pos | (sb->s_blocksize - 1)) + 1;
				break;
			}
			if (le64_to_cpu(de->inode)) {
				if (!dir_emit(ctx, de->name,
						de->name_len,
						le64_to_cpu(de->inode),
					fs_ftype_to_dtype(de->file_type))) {
					brelse(bh);
					return 0;
				}
				stored++;
			}
			offset += le16_to_cpu(de->rec_len);
			ctx->pos += le16_to_cpu(de->rec_len);
		}
		offset = 0;
		brelse(bh);
		bh = NULL;
		if (!persist && stored)
			break;
	}
	return 0;
}
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
struct super_block {int s_blocksize_bits; int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_dir_entry {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_2__ {unsigned long ip_dir_start_lookup; scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int NAMEI_RA_SIZE ; 
 int /*<<< orphan*/  OCFS2_BH_READAHEAD ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long) ; 
 int ocfs2_read_dir_block (struct inode*,unsigned long,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int ocfs2_search_dirblock (struct buffer_head*,struct inode*,char const*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_dir_entry**) ; 
 int /*<<< orphan*/  trace_ocfs2_find_entry_el (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *ocfs2_find_entry_el(const char *name, int namelen,
					       struct inode *dir,
					       struct ocfs2_dir_entry **res_dir)
{
	struct super_block *sb;
	struct buffer_head *bh_use[NAMEI_RA_SIZE];
	struct buffer_head *bh, *ret = NULL;
	unsigned long start, block, b;
	int ra_max = 0;		/* Number of bh's in the readahead
				   buffer, bh_use[] */
	int ra_ptr = 0;		/* Current index into readahead
				   buffer */
	int num = 0;
	int nblocks, i, err;

	sb = dir->i_sb;

	nblocks = i_size_read(dir) >> sb->s_blocksize_bits;
	start = OCFS2_I(dir)->ip_dir_start_lookup;
	if (start >= nblocks)
		start = 0;
	block = start;

restart:
	do {
		/*
		 * We deal with the read-ahead logic here.
		 */
		if (ra_ptr >= ra_max) {
			/* Refill the readahead buffer */
			ra_ptr = 0;
			b = block;
			for (ra_max = 0; ra_max < NAMEI_RA_SIZE; ra_max++) {
				/*
				 * Terminate if we reach the end of the
				 * directory and must wrap, or if our
				 * search has finished at this block.
				 */
				if (b >= nblocks || (num && block == start)) {
					bh_use[ra_max] = NULL;
					break;
				}
				num++;

				bh = NULL;
				err = ocfs2_read_dir_block(dir, b++, &bh,
							   OCFS2_BH_READAHEAD);
				bh_use[ra_max] = bh;
			}
		}
		if ((bh = bh_use[ra_ptr++]) == NULL)
			goto next;
		if (ocfs2_read_dir_block(dir, block, &bh, 0)) {
			/* read error, skip block & hope for the best.
			 * ocfs2_read_dir_block() has released the bh. */
			mlog(ML_ERROR, "reading directory %llu, "
				    "offset %lu\n",
				    (unsigned long long)OCFS2_I(dir)->ip_blkno,
				    block);
			goto next;
		}
		i = ocfs2_search_dirblock(bh, dir, name, namelen,
					  block << sb->s_blocksize_bits,
					  bh->b_data, sb->s_blocksize,
					  res_dir);
		if (i == 1) {
			OCFS2_I(dir)->ip_dir_start_lookup = block;
			ret = bh;
			goto cleanup_and_exit;
		} else {
			brelse(bh);
			if (i < 0)
				goto cleanup_and_exit;
		}
	next:
		if (++block >= nblocks)
			block = 0;
	} while (block != start);

	/*
	 * If the directory has grown while we were searching, then
	 * search the last part of the directory before giving up.
	 */
	block = nblocks;
	nblocks = i_size_read(dir) >> sb->s_blocksize_bits;
	if (block < nblocks) {
		start = 0;
		goto restart;
	}

cleanup_and_exit:
	/* Clean up the read-ahead blocks */
	for (; ra_ptr < ra_max; ra_ptr++)
		brelse(bh_use[ra_ptr]);

	trace_ocfs2_find_entry_el(ret);
	return ret;
}
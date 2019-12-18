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
typedef  scalar_t__ u64 ;
struct ocfs2_super {TYPE_1__* sb; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 struct buffer_head* __find_get_block (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_blocks_for_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_extent_map_get_blocks (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int ocfs2_read_blocks_sync (struct ocfs2_super*,scalar_t__,int,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_force_read_journal(struct inode *inode)
{
	int status = 0;
	int i;
	u64 v_blkno, p_blkno, p_blocks, num_blocks;
	struct buffer_head *bh = NULL;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	num_blocks = ocfs2_blocks_for_bytes(inode->i_sb, i_size_read(inode));
	v_blkno = 0;
	while (v_blkno < num_blocks) {
		status = ocfs2_extent_map_get_blocks(inode, v_blkno,
						     &p_blkno, &p_blocks, NULL);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}

		for (i = 0; i < p_blocks; i++, p_blkno++) {
			bh = __find_get_block(osb->sb->s_bdev, p_blkno,
					osb->sb->s_blocksize);
			/* block not cached. */
			if (!bh)
				continue;

			brelse(bh);
			bh = NULL;
			/* We are reading journal data which should not
			 * be put in the uptodate cache.
			 */
			status = ocfs2_read_blocks_sync(osb, p_blkno, 1, &bh);
			if (status < 0) {
				mlog_errno(status);
				goto bail;
			}

			brelse(bh);
			bh = NULL;
		}

		v_blkno += p_blocks;
	}

bail:
	return status;
}
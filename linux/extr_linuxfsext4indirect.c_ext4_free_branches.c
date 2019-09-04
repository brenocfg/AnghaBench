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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EXT4_ADDR_PER_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned long,int) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE_BLOCK (struct inode*,scalar_t__,char*) ; 
 int EXT4_FREE_BLOCKS_FORGET ; 
 int EXT4_FREE_BLOCKS_METADATA ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_data_block_valid (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ext4_free_data (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ext4_handle_is_aborted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_truncate_restart_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 struct buffer_head* sb_bread (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ try_to_extend_transaction (int /*<<< orphan*/ *,struct inode*) ; 

__attribute__((used)) static void ext4_free_branches(handle_t *handle, struct inode *inode,
			       struct buffer_head *parent_bh,
			       __le32 *first, __le32 *last, int depth)
{
	ext4_fsblk_t nr;
	__le32 *p;

	if (ext4_handle_is_aborted(handle))
		return;

	if (depth--) {
		struct buffer_head *bh;
		int addr_per_block = EXT4_ADDR_PER_BLOCK(inode->i_sb);
		p = last;
		while (--p >= first) {
			nr = le32_to_cpu(*p);
			if (!nr)
				continue;		/* A hole */

			if (!ext4_data_block_valid(EXT4_SB(inode->i_sb),
						   nr, 1)) {
				EXT4_ERROR_INODE(inode,
						 "invalid indirect mapped "
						 "block %lu (level %d)",
						 (unsigned long) nr, depth);
				break;
			}

			/* Go read the buffer for the next level down */
			bh = sb_bread(inode->i_sb, nr);

			/*
			 * A read failure? Report error and clear slot
			 * (should be rare).
			 */
			if (!bh) {
				EXT4_ERROR_INODE_BLOCK(inode, nr,
						       "Read failure");
				continue;
			}

			/* This zaps the entire block.  Bottom up. */
			BUFFER_TRACE(bh, "free child branches");
			ext4_free_branches(handle, inode, bh,
					(__le32 *) bh->b_data,
					(__le32 *) bh->b_data + addr_per_block,
					depth);
			brelse(bh);

			/*
			 * Everything below this this pointer has been
			 * released.  Now let this top-of-subtree go.
			 *
			 * We want the freeing of this indirect block to be
			 * atomic in the journal with the updating of the
			 * bitmap block which owns it.  So make some room in
			 * the journal.
			 *
			 * We zero the parent pointer *after* freeing its
			 * pointee in the bitmaps, so if extend_transaction()
			 * for some reason fails to put the bitmap changes and
			 * the release into the same transaction, recovery
			 * will merely complain about releasing a free block,
			 * rather than leaking blocks.
			 */
			if (ext4_handle_is_aborted(handle))
				return;
			if (try_to_extend_transaction(handle, inode)) {
				ext4_mark_inode_dirty(handle, inode);
				ext4_truncate_restart_trans(handle, inode,
					    ext4_blocks_for_truncate(inode));
			}

			/*
			 * The forget flag here is critical because if
			 * we are journaling (and not doing data
			 * journaling), we have to make sure a revoke
			 * record is written to prevent the journal
			 * replay from overwriting the (former)
			 * indirect block if it gets reallocated as a
			 * data block.  This must happen in the same
			 * transaction where the data blocks are
			 * actually freed.
			 */
			ext4_free_blocks(handle, inode, NULL, nr, 1,
					 EXT4_FREE_BLOCKS_METADATA|
					 EXT4_FREE_BLOCKS_FORGET);

			if (parent_bh) {
				/*
				 * The block which we have just freed is
				 * pointed to by an indirect block: journal it
				 */
				BUFFER_TRACE(parent_bh, "get_write_access");
				if (!ext4_journal_get_write_access(handle,
								   parent_bh)){
					*p = 0;
					BUFFER_TRACE(parent_bh,
					"call ext4_handle_dirty_metadata");
					ext4_handle_dirty_metadata(handle,
								   inode,
								   parent_bh);
				}
			}
		}
	} else {
		/* We have reached the bottom of the tree. */
		BUFFER_TRACE(parent_bh, "free data blocks");
		ext4_free_data(handle, inode, parent_bh, first, last);
	}
}
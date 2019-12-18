#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_7__* i_sb; } ;
struct ext4_inode_info {scalar_t__* i_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_14__ {unsigned int s_blocksize; } ;
struct TYPE_13__ {unsigned int s_bitmap_maxbytes; } ;
struct TYPE_12__ {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
struct TYPE_11__ {TYPE_2__* bh; scalar_t__* p; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXT4_ADDR_PER_BLOCK (TYPE_7__*) ; 
 unsigned int EXT4_BLOCK_SIZE_BITS (TYPE_7__*) ; 
#define  EXT4_DIND_BLOCK 130 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
#define  EXT4_IND_BLOCK 129 
 int EXT4_NDIR_BLOCKS ; 
 TYPE_6__* EXT4_SB (TYPE_7__*) ; 
#define  EXT4_TIND_BLOCK 128 
 int /*<<< orphan*/  brelse (TYPE_2__*) ; 
 int ext4_block_to_path (struct inode*,int,int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ext4_find_shared (struct inode*,int,int*,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  ext4_free_branches (int /*<<< orphan*/ *,struct inode*,TYPE_2__*,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ext4_free_data (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int min (int,int) ; 

int ext4_ind_remove_space(handle_t *handle, struct inode *inode,
			  ext4_lblk_t start, ext4_lblk_t end)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	__le32 *i_data = ei->i_data;
	int addr_per_block = EXT4_ADDR_PER_BLOCK(inode->i_sb);
	ext4_lblk_t offsets[4], offsets2[4];
	Indirect chain[4], chain2[4];
	Indirect *partial, *partial2;
	Indirect *p = NULL, *p2 = NULL;
	ext4_lblk_t max_block;
	__le32 nr = 0, nr2 = 0;
	int n = 0, n2 = 0;
	unsigned blocksize = inode->i_sb->s_blocksize;

	max_block = (EXT4_SB(inode->i_sb)->s_bitmap_maxbytes + blocksize-1)
					>> EXT4_BLOCK_SIZE_BITS(inode->i_sb);
	if (end >= max_block)
		end = max_block;
	if ((start >= end) || (start > max_block))
		return 0;

	n = ext4_block_to_path(inode, start, offsets, NULL);
	n2 = ext4_block_to_path(inode, end, offsets2, NULL);

	BUG_ON(n > n2);

	if ((n == 1) && (n == n2)) {
		/* We're punching only within direct block range */
		ext4_free_data(handle, inode, NULL, i_data + offsets[0],
			       i_data + offsets2[0]);
		return 0;
	} else if (n2 > n) {
		/*
		 * Start and end are on a different levels so we're going to
		 * free partial block at start, and partial block at end of
		 * the range. If there are some levels in between then
		 * do_indirects label will take care of that.
		 */

		if (n == 1) {
			/*
			 * Start is at the direct block level, free
			 * everything to the end of the level.
			 */
			ext4_free_data(handle, inode, NULL, i_data + offsets[0],
				       i_data + EXT4_NDIR_BLOCKS);
			goto end_range;
		}


		partial = p = ext4_find_shared(inode, n, offsets, chain, &nr);
		if (nr) {
			if (partial == chain) {
				/* Shared branch grows from the inode */
				ext4_free_branches(handle, inode, NULL,
					   &nr, &nr+1, (chain+n-1) - partial);
				*partial->p = 0;
			} else {
				/* Shared branch grows from an indirect block */
				BUFFER_TRACE(partial->bh, "get_write_access");
				ext4_free_branches(handle, inode, partial->bh,
					partial->p,
					partial->p+1, (chain+n-1) - partial);
			}
		}

		/*
		 * Clear the ends of indirect blocks on the shared branch
		 * at the start of the range
		 */
		while (partial > chain) {
			ext4_free_branches(handle, inode, partial->bh,
				partial->p + 1,
				(__le32 *)partial->bh->b_data+addr_per_block,
				(chain+n-1) - partial);
			partial--;
		}

end_range:
		partial2 = p2 = ext4_find_shared(inode, n2, offsets2, chain2, &nr2);
		if (nr2) {
			if (partial2 == chain2) {
				/*
				 * Remember, end is exclusive so here we're at
				 * the start of the next level we're not going
				 * to free. Everything was covered by the start
				 * of the range.
				 */
				goto do_indirects;
			}
		} else {
			/*
			 * ext4_find_shared returns Indirect structure which
			 * points to the last element which should not be
			 * removed by truncate. But this is end of the range
			 * in punch_hole so we need to point to the next element
			 */
			partial2->p++;
		}

		/*
		 * Clear the ends of indirect blocks on the shared branch
		 * at the end of the range
		 */
		while (partial2 > chain2) {
			ext4_free_branches(handle, inode, partial2->bh,
					   (__le32 *)partial2->bh->b_data,
					   partial2->p,
					   (chain2+n2-1) - partial2);
			partial2--;
		}
		goto do_indirects;
	}

	/* Punch happened within the same level (n == n2) */
	partial = p = ext4_find_shared(inode, n, offsets, chain, &nr);
	partial2 = p2 = ext4_find_shared(inode, n2, offsets2, chain2, &nr2);

	/* Free top, but only if partial2 isn't its subtree. */
	if (nr) {
		int level = min(partial - chain, partial2 - chain2);
		int i;
		int subtree = 1;

		for (i = 0; i <= level; i++) {
			if (offsets[i] != offsets2[i]) {
				subtree = 0;
				break;
			}
		}

		if (!subtree) {
			if (partial == chain) {
				/* Shared branch grows from the inode */
				ext4_free_branches(handle, inode, NULL,
						   &nr, &nr+1,
						   (chain+n-1) - partial);
				*partial->p = 0;
			} else {
				/* Shared branch grows from an indirect block */
				BUFFER_TRACE(partial->bh, "get_write_access");
				ext4_free_branches(handle, inode, partial->bh,
						   partial->p,
						   partial->p+1,
						   (chain+n-1) - partial);
			}
		}
	}

	if (!nr2) {
		/*
		 * ext4_find_shared returns Indirect structure which
		 * points to the last element which should not be
		 * removed by truncate. But this is end of the range
		 * in punch_hole so we need to point to the next element
		 */
		partial2->p++;
	}

	while (partial > chain || partial2 > chain2) {
		int depth = (chain+n-1) - partial;
		int depth2 = (chain2+n2-1) - partial2;

		if (partial > chain && partial2 > chain2 &&
		    partial->bh->b_blocknr == partial2->bh->b_blocknr) {
			/*
			 * We've converged on the same block. Clear the range,
			 * then we're done.
			 */
			ext4_free_branches(handle, inode, partial->bh,
					   partial->p + 1,
					   partial2->p,
					   (chain+n-1) - partial);
			goto cleanup;
		}

		/*
		 * The start and end partial branches may not be at the same
		 * level even though the punch happened within one level. So, we
		 * give them a chance to arrive at the same level, then walk
		 * them in step with each other until we converge on the same
		 * block.
		 */
		if (partial > chain && depth <= depth2) {
			ext4_free_branches(handle, inode, partial->bh,
					   partial->p + 1,
					   (__le32 *)partial->bh->b_data+addr_per_block,
					   (chain+n-1) - partial);
			partial--;
		}
		if (partial2 > chain2 && depth2 <= depth) {
			ext4_free_branches(handle, inode, partial2->bh,
					   (__le32 *)partial2->bh->b_data,
					   partial2->p,
					   (chain2+n2-1) - partial2);
			partial2--;
		}
	}

cleanup:
	while (p && p > chain) {
		BUFFER_TRACE(p->bh, "call brelse");
		brelse(p->bh);
		p--;
	}
	while (p2 && p2 > chain2) {
		BUFFER_TRACE(p2->bh, "call brelse");
		brelse(p2->bh);
		p2--;
	}
	return 0;

do_indirects:
	/* Kill the remaining (whole) subtrees */
	switch (offsets[0]) {
	default:
		if (++n >= n2)
			break;
		nr = i_data[EXT4_IND_BLOCK];
		if (nr) {
			ext4_free_branches(handle, inode, NULL, &nr, &nr+1, 1);
			i_data[EXT4_IND_BLOCK] = 0;
		}
		/* fall through */
	case EXT4_IND_BLOCK:
		if (++n >= n2)
			break;
		nr = i_data[EXT4_DIND_BLOCK];
		if (nr) {
			ext4_free_branches(handle, inode, NULL, &nr, &nr+1, 2);
			i_data[EXT4_DIND_BLOCK] = 0;
		}
		/* fall through */
	case EXT4_DIND_BLOCK:
		if (++n >= n2)
			break;
		nr = i_data[EXT4_TIND_BLOCK];
		if (nr) {
			ext4_free_branches(handle, inode, NULL, &nr, &nr+1, 3);
			i_data[EXT4_TIND_BLOCK] = 0;
		}
		/* fall through */
	case EXT4_TIND_BLOCK:
		;
	}
	goto cleanup;
}
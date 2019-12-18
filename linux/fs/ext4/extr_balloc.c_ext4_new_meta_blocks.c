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
struct ext4_allocation_request {unsigned long len; unsigned int flags; int /*<<< orphan*/  goal; struct inode* inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  int /*<<< orphan*/  ar ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_C2B (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int EXT4_MB_DELALLOC_RESERVED ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_alloc_block_nofail (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_mb_new_blocks (int /*<<< orphan*/ *,struct ext4_allocation_request*,int*) ; 
 int /*<<< orphan*/  memset (struct ext4_allocation_request*,int /*<<< orphan*/ ,int) ; 

ext4_fsblk_t ext4_new_meta_blocks(handle_t *handle, struct inode *inode,
				  ext4_fsblk_t goal, unsigned int flags,
				  unsigned long *count, int *errp)
{
	struct ext4_allocation_request ar;
	ext4_fsblk_t ret;

	memset(&ar, 0, sizeof(ar));
	/* Fill with neighbour allocated blocks */
	ar.inode = inode;
	ar.goal = goal;
	ar.len = count ? *count : 1;
	ar.flags = flags;

	ret = ext4_mb_new_blocks(handle, &ar, errp);
	if (count)
		*count = ar.len;
	/*
	 * Account for the allocated meta blocks.  We will never
	 * fail EDQUOT for metdata, but we do account for it.
	 */
	if (!(*errp) && (flags & EXT4_MB_DELALLOC_RESERVED)) {
		dquot_alloc_block_nofail(inode,
				EXT4_C2B(EXT4_SB(inode->i_sb), ar.len));
	}
	return ret;
}
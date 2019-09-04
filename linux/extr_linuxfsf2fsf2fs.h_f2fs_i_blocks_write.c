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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  FI_AUTO_RECOVER ; 
 int /*<<< orphan*/  FI_DIRTY_INODE ; 
 int /*<<< orphan*/  dquot_alloc_block_nofail (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_claim_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_free_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void f2fs_i_blocks_write(struct inode *inode,
					block_t diff, bool add, bool claim)
{
	bool clean = !is_inode_flag_set(inode, FI_DIRTY_INODE);
	bool recover = is_inode_flag_set(inode, FI_AUTO_RECOVER);

	/* add = 1, claim = 1 should be dquot_reserve_block in pair */
	if (add) {
		if (claim)
			dquot_claim_block(inode, diff);
		else
			dquot_alloc_block_nofail(inode, diff);
	} else {
		dquot_free_block(inode, diff);
	}

	f2fs_mark_inode_dirty_sync(inode, true);
	if (clean || recover)
		set_inode_flag(inode, FI_AUTO_RECOVER);
}
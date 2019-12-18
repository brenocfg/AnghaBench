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
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct TYPE_2__ {scalar_t__ objectid; } ;
struct btrfs_root {int /*<<< orphan*/  state; TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_HEADER_FLAG_RELOC ; 
 int /*<<< orphan*/  BTRFS_HEADER_FLAG_WRITTEN ; 
 int /*<<< orphan*/  BTRFS_ROOT_FORCE_COW ; 
 scalar_t__ BTRFS_TREE_RELOC_OBJECTID ; 
 scalar_t__ btrfs_header_flag (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 scalar_t__ btrfs_is_testing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int should_cow_block(struct btrfs_trans_handle *trans,
				   struct btrfs_root *root,
				   struct extent_buffer *buf)
{
	if (btrfs_is_testing(root->fs_info))
		return 0;

	/* Ensure we can see the FORCE_COW bit */
	smp_mb__before_atomic();

	/*
	 * We do not need to cow a block if
	 * 1) this block is not created or changed in this transaction;
	 * 2) this block does not belong to TREE_RELOC tree;
	 * 3) the root is not forced COW.
	 *
	 * What is forced COW:
	 *    when we create snapshot during committing the transaction,
	 *    after we've finished copying src root, we must COW the shared
	 *    block to ensure the metadata consistency.
	 */
	if (btrfs_header_generation(buf) == trans->transid &&
	    !btrfs_header_flag(buf, BTRFS_HEADER_FLAG_WRITTEN) &&
	    !(root->root_key.objectid != BTRFS_TREE_RELOC_OBJECTID &&
	      btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC)) &&
	    !test_bit(BTRFS_ROOT_FORCE_COW, &root->state))
		return 0;
	return 1;
}
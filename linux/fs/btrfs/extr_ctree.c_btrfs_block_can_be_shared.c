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
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  root_item; struct extent_buffer* commit_root; struct extent_buffer* node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_HEADER_FLAG_RELOC ; 
 int /*<<< orphan*/  BTRFS_ROOT_REF_COWS ; 
 scalar_t__ btrfs_header_flag (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 scalar_t__ btrfs_root_last_snapshot (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_block_can_be_shared(struct btrfs_root *root,
			      struct extent_buffer *buf)
{
	/*
	 * Tree blocks not in reference counted trees and tree roots
	 * are never shared. If a block was allocated after the last
	 * snapshot and the block was not allocated by tree relocation,
	 * we know the block is not shared.
	 */
	if (test_bit(BTRFS_ROOT_REF_COWS, &root->state) &&
	    buf != root->node && buf != root->commit_root &&
	    (btrfs_header_generation(buf) <=
	     btrfs_root_last_snapshot(&root->root_item) ||
	     btrfs_header_flag(buf, BTRFS_HEADER_FLAG_RELOC)))
		return 1;

	return 0;
}
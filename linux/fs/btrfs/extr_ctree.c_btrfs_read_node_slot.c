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
struct extent_buffer {int /*<<< orphan*/  fs_info; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 struct extent_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 struct extent_buffer* read_tree_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

struct extent_buffer *btrfs_read_node_slot(struct extent_buffer *parent,
					   int slot)
{
	int level = btrfs_header_level(parent);
	struct extent_buffer *eb;
	struct btrfs_key first_key;

	if (slot < 0 || slot >= btrfs_header_nritems(parent))
		return ERR_PTR(-ENOENT);

	BUG_ON(level == 0);

	btrfs_node_key_to_cpu(parent, &first_key, slot);
	eb = read_tree_block(parent->fs_info, btrfs_node_blockptr(parent, slot),
			     btrfs_node_ptr_generation(parent, slot),
			     level - 1, &first_key);
	if (!IS_ERR(eb) && !extent_buffer_uptodate(eb)) {
		free_extent_buffer(eb);
		eb = ERR_PTR(-EIO);
	}

	return eb;
}
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
typedef  int u32 ;
struct extent_buffer {struct btrfs_fs_info* fs_info; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_NODEPTRS_PER_BLOCK (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_bytenr (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_generation (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_owner (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_is_leaf (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_print_leaf (struct extent_buffer*) ; 
 int /*<<< orphan*/  extent_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_eb_refs_lock (struct extent_buffer*) ; 
 struct extent_buffer* read_tree_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

void btrfs_print_tree(struct extent_buffer *c, bool follow)
{
	struct btrfs_fs_info *fs_info;
	int i; u32 nr;
	struct btrfs_key key;
	int level;

	if (!c)
		return;
	fs_info = c->fs_info;
	nr = btrfs_header_nritems(c);
	level = btrfs_header_level(c);
	if (level == 0) {
		btrfs_print_leaf(c);
		return;
	}
	btrfs_info(fs_info,
		   "node %llu level %d gen %llu total ptrs %d free spc %u owner %llu",
		   btrfs_header_bytenr(c), level, btrfs_header_generation(c),
		   nr, (u32)BTRFS_NODEPTRS_PER_BLOCK(fs_info) - nr,
		   btrfs_header_owner(c));
	print_eb_refs_lock(c);
	for (i = 0; i < nr; i++) {
		btrfs_node_key_to_cpu(c, &key, i);
		pr_info("\tkey %d (%llu %u %llu) block %llu gen %llu\n",
		       i, key.objectid, key.type, key.offset,
		       btrfs_node_blockptr(c, i),
		       btrfs_node_ptr_generation(c, i));
	}
	if (!follow)
		return;
	for (i = 0; i < nr; i++) {
		struct btrfs_key first_key;
		struct extent_buffer *next;

		btrfs_node_key_to_cpu(c, &first_key, i);
		next = read_tree_block(fs_info, btrfs_node_blockptr(c, i),
				       btrfs_node_ptr_generation(c, i),
				       level - 1, &first_key);
		if (IS_ERR(next)) {
			continue;
		} else if (!extent_buffer_uptodate(next)) {
			free_extent_buffer(next);
			continue;
		}

		if (btrfs_is_leaf(next) &&
		   level != 1)
			BUG();
		if (btrfs_header_level(next) !=
		       level - 1)
			BUG();
		btrfs_print_tree(next, follow);
		free_extent_buffer(next);
	}
}
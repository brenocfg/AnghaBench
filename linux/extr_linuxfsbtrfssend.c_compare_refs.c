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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct send_ctx {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_inode_extref {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_INODE_REF_KEY ; 
 int btrfs_inode_extref_name_len (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 scalar_t__ btrfs_inode_extref_parent (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int dir_changed (struct send_ctx*,scalar_t__) ; 

__attribute__((used)) static int compare_refs(struct send_ctx *sctx, struct btrfs_path *path,
			struct btrfs_key *key)
{
	struct btrfs_inode_extref *extref;
	struct extent_buffer *leaf;
	u64 dirid = 0, last_dirid = 0;
	unsigned long ptr;
	u32 item_size;
	u32 cur_offset = 0;
	int ref_name_len;
	int ret = 0;

	/* Easy case, just check this one dirid */
	if (key->type == BTRFS_INODE_REF_KEY) {
		dirid = key->offset;

		ret = dir_changed(sctx, dirid);
		goto out;
	}

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	while (cur_offset < item_size) {
		extref = (struct btrfs_inode_extref *)(ptr +
						       cur_offset);
		dirid = btrfs_inode_extref_parent(leaf, extref);
		ref_name_len = btrfs_inode_extref_name_len(leaf, extref);
		cur_offset += ref_name_len + sizeof(*extref);
		if (dirid == last_dirid)
			continue;
		ret = dir_changed(sctx, dirid);
		if (ret)
			break;
		last_dirid = dirid;
	}
out:
	return ret;
}
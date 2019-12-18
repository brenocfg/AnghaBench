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
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_inode_extref {int dummy; } ;
struct btrfs_inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int btrfs_find_one_extref (struct btrfs_root*,scalar_t__,scalar_t__,struct btrfs_path*,struct btrfs_inode_extref**,scalar_t__*) ; 
 scalar_t__ btrfs_ino (struct btrfs_inode*) ; 
 int btrfs_inode_extref_name_len (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 

__attribute__((used)) static int count_inode_extrefs(struct btrfs_root *root,
		struct btrfs_inode *inode, struct btrfs_path *path)
{
	int ret = 0;
	int name_len;
	unsigned int nlink = 0;
	u32 item_size;
	u32 cur_offset = 0;
	u64 inode_objectid = btrfs_ino(inode);
	u64 offset = 0;
	unsigned long ptr;
	struct btrfs_inode_extref *extref;
	struct extent_buffer *leaf;

	while (1) {
		ret = btrfs_find_one_extref(root, inode_objectid, offset, path,
					    &extref, &offset);
		if (ret)
			break;

		leaf = path->nodes[0];
		item_size = btrfs_item_size_nr(leaf, path->slots[0]);
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		cur_offset = 0;

		while (cur_offset < item_size) {
			extref = (struct btrfs_inode_extref *) (ptr + cur_offset);
			name_len = btrfs_inode_extref_name_len(leaf, extref);

			nlink++;

			cur_offset += name_len + sizeof(*extref);
		}

		offset++;
		btrfs_release_path(path);
	}
	btrfs_release_path(path);

	if (ret < 0 && ret != -ENOENT)
		return ret;
	return nlink;
}
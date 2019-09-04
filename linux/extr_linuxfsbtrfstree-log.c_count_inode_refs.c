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
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_inode_ref {int dummy; } ;
struct btrfs_inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_INODE_REF_KEY ; 
 scalar_t__ btrfs_ino (struct btrfs_inode*) ; 
 int btrfs_inode_ref_name_len (int /*<<< orphan*/ ,struct btrfs_inode_ref*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,scalar_t__) ; 
 unsigned long btrfs_item_ptr_offset (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long btrfs_item_size_nr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_inode_refs(struct btrfs_root *root,
			struct btrfs_inode *inode, struct btrfs_path *path)
{
	int ret;
	struct btrfs_key key;
	unsigned int nlink = 0;
	unsigned long ptr;
	unsigned long ptr_end;
	int name_len;
	u64 ino = btrfs_ino(inode);

	key.objectid = ino;
	key.type = BTRFS_INODE_REF_KEY;
	key.offset = (u64)-1;

	while (1) {
		ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
		if (ret < 0)
			break;
		if (ret > 0) {
			if (path->slots[0] == 0)
				break;
			path->slots[0]--;
		}
process_slot:
		btrfs_item_key_to_cpu(path->nodes[0], &key,
				      path->slots[0]);
		if (key.objectid != ino ||
		    key.type != BTRFS_INODE_REF_KEY)
			break;
		ptr = btrfs_item_ptr_offset(path->nodes[0], path->slots[0]);
		ptr_end = ptr + btrfs_item_size_nr(path->nodes[0],
						   path->slots[0]);
		while (ptr < ptr_end) {
			struct btrfs_inode_ref *ref;

			ref = (struct btrfs_inode_ref *)ptr;
			name_len = btrfs_inode_ref_name_len(path->nodes[0],
							    ref);
			ptr = (unsigned long)(ref + 1) + name_len;
			nlink++;
		}

		if (key.offset == 0)
			break;
		if (path->slots[0] > 0) {
			path->slots[0]--;
			goto process_slot;
		}
		key.offset--;
		btrfs_release_path(path);
	}
	btrfs_release_path(path);

	return nlink;
}
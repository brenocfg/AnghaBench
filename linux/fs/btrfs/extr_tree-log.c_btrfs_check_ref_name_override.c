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
struct btrfs_path {int search_commit_root; int skip_locking; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ type; scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_inode_ref {int dummy; } ;
struct btrfs_inode_extref {int /*<<< orphan*/  name; } ;
struct btrfs_inode {int /*<<< orphan*/  root; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_INODE_ITEM_KEY ; 
 scalar_t__ BTRFS_INODE_REF_KEY ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_dir_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_dir_item*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 scalar_t__ btrfs_inode_extref_name_len (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 scalar_t__ btrfs_inode_extref_parent (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 scalar_t__ btrfs_inode_ref_name_len (struct extent_buffer*,struct btrfs_inode_ref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int const) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int const) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_path*,scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* krealloc (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,unsigned long,scalar_t__) ; 

__attribute__((used)) static int btrfs_check_ref_name_override(struct extent_buffer *eb,
					 const int slot,
					 const struct btrfs_key *key,
					 struct btrfs_inode *inode,
					 u64 *other_ino, u64 *other_parent)
{
	int ret;
	struct btrfs_path *search_path;
	char *name = NULL;
	u32 name_len = 0;
	u32 item_size = btrfs_item_size_nr(eb, slot);
	u32 cur_offset = 0;
	unsigned long ptr = btrfs_item_ptr_offset(eb, slot);

	search_path = btrfs_alloc_path();
	if (!search_path)
		return -ENOMEM;
	search_path->search_commit_root = 1;
	search_path->skip_locking = 1;

	while (cur_offset < item_size) {
		u64 parent;
		u32 this_name_len;
		u32 this_len;
		unsigned long name_ptr;
		struct btrfs_dir_item *di;

		if (key->type == BTRFS_INODE_REF_KEY) {
			struct btrfs_inode_ref *iref;

			iref = (struct btrfs_inode_ref *)(ptr + cur_offset);
			parent = key->offset;
			this_name_len = btrfs_inode_ref_name_len(eb, iref);
			name_ptr = (unsigned long)(iref + 1);
			this_len = sizeof(*iref) + this_name_len;
		} else {
			struct btrfs_inode_extref *extref;

			extref = (struct btrfs_inode_extref *)(ptr +
							       cur_offset);
			parent = btrfs_inode_extref_parent(eb, extref);
			this_name_len = btrfs_inode_extref_name_len(eb, extref);
			name_ptr = (unsigned long)&extref->name;
			this_len = sizeof(*extref) + this_name_len;
		}

		if (this_name_len > name_len) {
			char *new_name;

			new_name = krealloc(name, this_name_len, GFP_NOFS);
			if (!new_name) {
				ret = -ENOMEM;
				goto out;
			}
			name_len = this_name_len;
			name = new_name;
		}

		read_extent_buffer(eb, name, name_ptr, this_name_len);
		di = btrfs_lookup_dir_item(NULL, inode->root, search_path,
				parent, name, this_name_len, 0);
		if (di && !IS_ERR(di)) {
			struct btrfs_key di_key;

			btrfs_dir_item_key_to_cpu(search_path->nodes[0],
						  di, &di_key);
			if (di_key.type == BTRFS_INODE_ITEM_KEY) {
				if (di_key.objectid != key->objectid) {
					ret = 1;
					*other_ino = di_key.objectid;
					*other_parent = parent;
				} else {
					ret = 0;
				}
			} else {
				ret = -EAGAIN;
			}
			goto out;
		} else if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		}
		btrfs_release_path(search_path);

		cur_offset += this_len;
	}
	ret = 0;
out:
	btrfs_free_path(search_path);
	kfree(name);
	return ret;
}
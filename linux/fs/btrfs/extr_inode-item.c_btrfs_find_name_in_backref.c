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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_inode_ref {int dummy; } ;

/* Variables and functions */
 int btrfs_inode_ref_name_len (struct extent_buffer*,struct btrfs_inode_ref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,char const*,unsigned long,int) ; 

struct btrfs_inode_ref *btrfs_find_name_in_backref(struct extent_buffer *leaf,
						   int slot, const char *name,
						   int name_len)
{
	struct btrfs_inode_ref *ref;
	unsigned long ptr;
	unsigned long name_ptr;
	u32 item_size;
	u32 cur_offset = 0;
	int len;

	item_size = btrfs_item_size_nr(leaf, slot);
	ptr = btrfs_item_ptr_offset(leaf, slot);
	while (cur_offset < item_size) {
		ref = (struct btrfs_inode_ref *)(ptr + cur_offset);
		len = btrfs_inode_ref_name_len(leaf, ref);
		name_ptr = (unsigned long)(ref + 1);
		cur_offset += len + sizeof(*ref);
		if (len != name_len)
			continue;
		if (memcmp_extent_buffer(leaf, name, name_ptr, name_len) == 0)
			return ref;
	}
	return NULL;
}
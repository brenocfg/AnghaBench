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
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_xattr_entry {int e_name_len; scalar_t__ e_name_index; int /*<<< orphan*/  e_value_size; int /*<<< orphan*/  e_value_inum; int /*<<< orphan*/  e_name; } ;
struct ext4_inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ EXT4_XATTR_INDEX_SYSTEM ; 
 unsigned int EXT4_XATTR_LEN (int) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 scalar_t__ EXT4_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 struct ext4_xattr_entry* IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* IHDR (struct inode*,struct ext4_inode*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 int ext4_xattr_move_to_block (int /*<<< orphan*/ *,struct inode*,struct ext4_inode*,struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ext4_xattr_make_inode_space(handle_t *handle, struct inode *inode,
				       struct ext4_inode *raw_inode,
				       int isize_diff, size_t ifree,
				       size_t bfree, int *total_ino)
{
	struct ext4_xattr_ibody_header *header = IHDR(inode, raw_inode);
	struct ext4_xattr_entry *small_entry;
	struct ext4_xattr_entry *entry;
	struct ext4_xattr_entry *last;
	unsigned int entry_size;	/* EA entry size */
	unsigned int total_size;	/* EA entry size + value size */
	unsigned int min_total_size;
	int error;

	while (isize_diff > ifree) {
		entry = NULL;
		small_entry = NULL;
		min_total_size = ~0U;
		last = IFIRST(header);
		/* Find the entry best suited to be pushed into EA block */
		for (; !IS_LAST_ENTRY(last); last = EXT4_XATTR_NEXT(last)) {
			/* never move system.data out of the inode */
			if ((last->e_name_len == 4) &&
			    (last->e_name_index == EXT4_XATTR_INDEX_SYSTEM) &&
			    !memcmp(last->e_name, "data", 4))
				continue;
			total_size = EXT4_XATTR_LEN(last->e_name_len);
			if (!last->e_value_inum)
				total_size += EXT4_XATTR_SIZE(
					       le32_to_cpu(last->e_value_size));
			if (total_size <= bfree &&
			    total_size < min_total_size) {
				if (total_size + ifree < isize_diff) {
					small_entry = last;
				} else {
					entry = last;
					min_total_size = total_size;
				}
			}
		}

		if (entry == NULL) {
			if (small_entry == NULL)
				return -ENOSPC;
			entry = small_entry;
		}

		entry_size = EXT4_XATTR_LEN(entry->e_name_len);
		total_size = entry_size;
		if (!entry->e_value_inum)
			total_size += EXT4_XATTR_SIZE(
					      le32_to_cpu(entry->e_value_size));
		error = ext4_xattr_move_to_block(handle, inode, raw_inode,
						 entry);
		if (error)
			return error;

		*total_ino -= entry_size;
		ifree += total_size;
		bfree -= total_size;
	}

	return 0;
}
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
typedef  int u16 ;
struct ext4_xattr_entry {scalar_t__ e_name_len; scalar_t__ e_value_inum; int /*<<< orphan*/  e_value_offs; int /*<<< orphan*/  e_value_size; int /*<<< orphan*/  e_name; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int EXT4_XATTR_SIZE (scalar_t__) ; 
 scalar_t__ EXT4_XATTR_SIZE_MAX ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ext4_xattr_check_entries(struct ext4_xattr_entry *entry, void *end,
			 void *value_start)
{
	struct ext4_xattr_entry *e = entry;

	/* Find the end of the names list */
	while (!IS_LAST_ENTRY(e)) {
		struct ext4_xattr_entry *next = EXT4_XATTR_NEXT(e);
		if ((void *)next >= end)
			return -EFSCORRUPTED;
		if (strnlen(e->e_name, e->e_name_len) != e->e_name_len)
			return -EFSCORRUPTED;
		e = next;
	}

	/* Check the values */
	while (!IS_LAST_ENTRY(entry)) {
		u32 size = le32_to_cpu(entry->e_value_size);

		if (size > EXT4_XATTR_SIZE_MAX)
			return -EFSCORRUPTED;

		if (size != 0 && entry->e_value_inum == 0) {
			u16 offs = le16_to_cpu(entry->e_value_offs);
			void *value;

			/*
			 * The value cannot overlap the names, and the value
			 * with padding cannot extend beyond 'end'.  Check both
			 * the padded and unpadded sizes, since the size may
			 * overflow to 0 when adding padding.
			 */
			if (offs > end - value_start)
				return -EFSCORRUPTED;
			value = value_start + offs;
			if (value < (void *)e + sizeof(u32) ||
			    size > end - value ||
			    EXT4_XATTR_SIZE(size) > end - value)
				return -EFSCORRUPTED;
		}
		entry = EXT4_XATTR_NEXT(entry);
	}

	return 0;
}
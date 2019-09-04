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
struct ext4_xattr_entry {int e_name_index; size_t e_name_len; int /*<<< orphan*/  e_name; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 int /*<<< orphan*/  IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 int memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int
xattr_find_entry(struct inode *inode, struct ext4_xattr_entry **pentry,
		 void *end, int name_index, const char *name, int sorted)
{
	struct ext4_xattr_entry *entry, *next;
	size_t name_len;
	int cmp = 1;

	if (name == NULL)
		return -EINVAL;
	name_len = strlen(name);
	for (entry = *pentry; !IS_LAST_ENTRY(entry); entry = next) {
		next = EXT4_XATTR_NEXT(entry);
		if ((void *) next >= end) {
			EXT4_ERROR_INODE(inode, "corrupted xattr entries");
			return -EFSCORRUPTED;
		}
		cmp = name_index - entry->e_name_index;
		if (!cmp)
			cmp = name_len - entry->e_name_len;
		if (!cmp)
			cmp = memcmp(name, entry->e_name, name_len);
		if (cmp <= 0 && (sorted || cmp == 0))
			break;
	}
	*pentry = entry;
	return cmp ? -ENODATA : 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_xattr_entry {char* e_name; int e_name_len; int /*<<< orphan*/  e_value_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_xattr_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 unsigned int F2FS_NAME_LEN ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int lookup_all_xattrs (struct inode*,struct page*,int,unsigned int,char const*,struct f2fs_xattr_entry**,void**,int*) ; 
 int /*<<< orphan*/  memcpy (void*,char*,unsigned int) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int f2fs_getxattr(struct inode *inode, int index, const char *name,
		void *buffer, size_t buffer_size, struct page *ipage)
{
	struct f2fs_xattr_entry *entry = NULL;
	int error = 0;
	unsigned int size, len;
	void *base_addr = NULL;
	int base_size;

	if (name == NULL)
		return -EINVAL;

	len = strlen(name);
	if (len > F2FS_NAME_LEN)
		return -ERANGE;

	down_read(&F2FS_I(inode)->i_xattr_sem);
	error = lookup_all_xattrs(inode, ipage, index, len, name,
				&entry, &base_addr, &base_size);
	up_read(&F2FS_I(inode)->i_xattr_sem);
	if (error)
		return error;

	size = le16_to_cpu(entry->e_value_size);

	if (buffer && size > buffer_size) {
		error = -ERANGE;
		goto out;
	}

	if (buffer) {
		char *pval = entry->e_name + entry->e_name_len;

		if (base_size - (pval - (char *)base_addr) < size) {
			error = -ERANGE;
			goto out;
		}
		memcpy(buffer, pval, size);
	}
	error = size;
out:
	kvfree(base_addr);
	return error;
}
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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; } ;
struct f2fs_xattr_entry {int e_name_index; size_t e_name_len; char* e_name; int /*<<< orphan*/  e_value_size; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  i_acl_mode; int /*<<< orphan*/  i_xattr_nid; } ;

/* Variables and functions */
 int E2BIG ; 
 int EEXIST ; 
 int EFSCORRUPTED ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENTRY_SIZE (struct f2fs_xattr_entry*) ; 
 int ERANGE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 size_t F2FS_NAME_LEN ; 
 int F2FS_XATTR_INDEX_ENCRYPTION ; 
 int /*<<< orphan*/  F2FS_XATTR_NAME_ENCRYPTION_CONTEXT ; 
 int /*<<< orphan*/  FI_ACL_MODE ; 
 scalar_t__ IS_XATTR_LAST_ENTRY (struct f2fs_xattr_entry*) ; 
 size_t MAX_VALUE_LEN (struct inode*) ; 
 int MIN_OFFSET (struct inode*) ; 
 int /*<<< orphan*/  SBI_NEED_CP ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int XATTR_ALIGN (int) ; 
 int XATTR_CREATE ; 
 struct f2fs_xattr_entry* XATTR_NEXT_ENTRY (struct f2fs_xattr_entry*) ; 
 int XATTR_REPLACE ; 
 int XATTR_SIZE (int /*<<< orphan*/ ,struct inode*) ; 
 struct f2fs_xattr_entry* __find_xattr (void*,void*,int,size_t,char const*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  f2fs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_set_encrypted_inode (struct inode*) ; 
 scalar_t__ f2fs_xattr_value_same (struct f2fs_xattr_entry*,void const*,size_t) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memmove (struct f2fs_xattr_entry*,struct f2fs_xattr_entry*,int) ; 
 int /*<<< orphan*/  memset (struct f2fs_xattr_entry*,int /*<<< orphan*/ ,int) ; 
 int read_all_xattrs (struct inode*,struct page*,void**) ; 
 int /*<<< orphan*/  set_sbi_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 
 int write_all_xattrs (struct inode*,int,void*,struct page*) ; 

__attribute__((used)) static int __f2fs_setxattr(struct inode *inode, int index,
			const char *name, const void *value, size_t size,
			struct page *ipage, int flags)
{
	struct f2fs_xattr_entry *here, *last;
	void *base_addr, *last_base_addr;
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	int found, newsize;
	size_t len;
	__u32 new_hsize;
	int error = 0;

	if (name == NULL)
		return -EINVAL;

	if (value == NULL)
		size = 0;

	len = strlen(name);

	if (len > F2FS_NAME_LEN)
		return -ERANGE;

	if (size > MAX_VALUE_LEN(inode))
		return -E2BIG;

	error = read_all_xattrs(inode, ipage, &base_addr);
	if (error)
		return error;

	last_base_addr = (void *)base_addr + XATTR_SIZE(xnid, inode);

	/* find entry with wanted name. */
	here = __find_xattr(base_addr, last_base_addr, index, len, name);
	if (!here) {
		f2fs_err(F2FS_I_SB(inode), "inode (%lu) has corrupted xattr",
								inode->i_ino);
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
		error = -EFSCORRUPTED;
		goto exit;
	}

	found = IS_XATTR_LAST_ENTRY(here) ? 0 : 1;

	if (found) {
		if ((flags & XATTR_CREATE)) {
			error = -EEXIST;
			goto exit;
		}

		if (value && f2fs_xattr_value_same(here, value, size))
			goto exit;
	} else if ((flags & XATTR_REPLACE)) {
		error = -ENODATA;
		goto exit;
	}

	last = here;
	while (!IS_XATTR_LAST_ENTRY(last))
		last = XATTR_NEXT_ENTRY(last);

	newsize = XATTR_ALIGN(sizeof(struct f2fs_xattr_entry) + len + size);

	/* 1. Check space */
	if (value) {
		int free;
		/*
		 * If value is NULL, it is remove operation.
		 * In case of update operation, we calculate free.
		 */
		free = MIN_OFFSET(inode) - ((char *)last - (char *)base_addr);
		if (found)
			free = free + ENTRY_SIZE(here);

		if (unlikely(free < newsize)) {
			error = -E2BIG;
			goto exit;
		}
	}

	/* 2. Remove old entry */
	if (found) {
		/*
		 * If entry is found, remove old entry.
		 * If not found, remove operation is not needed.
		 */
		struct f2fs_xattr_entry *next = XATTR_NEXT_ENTRY(here);
		int oldsize = ENTRY_SIZE(here);

		memmove(here, next, (char *)last - (char *)next);
		last = (struct f2fs_xattr_entry *)((char *)last - oldsize);
		memset(last, 0, oldsize);
	}

	new_hsize = (char *)last - (char *)base_addr;

	/* 3. Write new entry */
	if (value) {
		char *pval;
		/*
		 * Before we come here, old entry is removed.
		 * We just write new entry.
		 */
		last->e_name_index = index;
		last->e_name_len = len;
		memcpy(last->e_name, name, len);
		pval = last->e_name + len;
		memcpy(pval, value, size);
		last->e_value_size = cpu_to_le16(size);
		new_hsize += newsize;
	}

	error = write_all_xattrs(inode, new_hsize, base_addr, ipage);
	if (error)
		goto exit;

	if (is_inode_flag_set(inode, FI_ACL_MODE)) {
		inode->i_mode = F2FS_I(inode)->i_acl_mode;
		inode->i_ctime = current_time(inode);
		clear_inode_flag(inode, FI_ACL_MODE);
	}
	if (index == F2FS_XATTR_INDEX_ENCRYPTION &&
			!strcmp(name, F2FS_XATTR_NAME_ENCRYPTION_CONTEXT))
		f2fs_set_encrypted_inode(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
	if (!error && S_ISDIR(inode->i_mode))
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_CP);
exit:
	kvfree(base_addr);
	return error;
}
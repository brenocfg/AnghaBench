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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct fscrypt_name {int dummy; } ;
struct f2fs_dir_entry {int dummy; } ;
struct TYPE_2__ {unsigned int i_current_depth; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 unsigned int MAX_DIR_HASH_DEPTH ; 
 int /*<<< orphan*/  current ; 
 unsigned long dir_blocks (struct inode*) ; 
 struct f2fs_dir_entry* f2fs_find_in_inline_dir (struct inode*,struct fscrypt_name*,struct page**) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_depth_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct f2fs_dir_entry* find_in_level (struct inode*,unsigned int,struct fscrypt_name*,struct page**) ; 
 scalar_t__ unlikely (int) ; 

struct f2fs_dir_entry *__f2fs_find_entry(struct inode *dir,
			struct fscrypt_name *fname, struct page **res_page)
{
	unsigned long npages = dir_blocks(dir);
	struct f2fs_dir_entry *de = NULL;
	unsigned int max_depth;
	unsigned int level;

	if (f2fs_has_inline_dentry(dir)) {
		*res_page = NULL;
		de = f2fs_find_in_inline_dir(dir, fname, res_page);
		goto out;
	}

	if (npages == 0) {
		*res_page = NULL;
		goto out;
	}

	max_depth = F2FS_I(dir)->i_current_depth;
	if (unlikely(max_depth > MAX_DIR_HASH_DEPTH)) {
		f2fs_warn(F2FS_I_SB(dir), "Corrupted max_depth of %lu: %u",
			  dir->i_ino, max_depth);
		max_depth = MAX_DIR_HASH_DEPTH;
		f2fs_i_depth_write(dir, max_depth);
	}

	for (level = 0; level < max_depth; level++) {
		*res_page = NULL;
		de = find_in_level(dir, level, fname, res_page);
		if (de || IS_ERR(*res_page))
			break;
	}
out:
	/* This is to increase the speed of f2fs_create */
	if (!de)
		F2FS_I(dir)->task = current;
	return de;
}
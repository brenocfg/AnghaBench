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
struct qstr {int dummy; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct fscrypt_name {int dummy; } ;
struct f2fs_dir_entry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct page* ERR_PTR (int) ; 
 struct f2fs_dir_entry* __f2fs_find_entry (struct inode*,struct fscrypt_name*,struct page**) ; 
 int /*<<< orphan*/  fscrypt_free_filename (struct fscrypt_name*) ; 
 int fscrypt_setup_filename (struct inode*,struct qstr const*,int,struct fscrypt_name*) ; 

struct f2fs_dir_entry *f2fs_find_entry(struct inode *dir,
			const struct qstr *child, struct page **res_page)
{
	struct f2fs_dir_entry *de = NULL;
	struct fscrypt_name fname;
	int err;

	err = fscrypt_setup_filename(dir, child, 1, &fname);
	if (err) {
		if (err == -ENOENT)
			*res_page = NULL;
		else
			*res_page = ERR_PTR(err);
		return NULL;
	}

	de = __f2fs_find_entry(dir, &fname, res_page);

	fscrypt_free_filename(&fname);
	return de;
}
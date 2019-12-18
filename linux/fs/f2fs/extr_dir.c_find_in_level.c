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
struct qstr {int /*<<< orphan*/  len; } ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct fscrypt_name {int /*<<< orphan*/  disk_name; } ;
struct f2fs_dir_entry {int dummy; } ;
typedef  scalar_t__ f2fs_hash_t ;
struct TYPE_2__ {scalar_t__ chash; unsigned int clevel; int /*<<< orphan*/  i_dir_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct qstr FSTR_TO_QSTR (int /*<<< orphan*/ *) ; 
 int GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int /*<<< orphan*/  PTR_ERR (struct page*) ; 
 unsigned int bucket_blocks (unsigned int) ; 
 unsigned int dir_block_index (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int dir_buckets (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_dentry_hash (struct inode*,struct qstr*,struct fscrypt_name*) ; 
 struct page* f2fs_find_data_page (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 struct f2fs_dir_entry* find_in_block (struct inode*,struct page*,struct fscrypt_name*,scalar_t__,int*,struct page**) ; 
 unsigned int le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static struct f2fs_dir_entry *find_in_level(struct inode *dir,
					unsigned int level,
					struct fscrypt_name *fname,
					struct page **res_page)
{
	struct qstr name = FSTR_TO_QSTR(&fname->disk_name);
	int s = GET_DENTRY_SLOTS(name.len);
	unsigned int nbucket, nblock;
	unsigned int bidx, end_block;
	struct page *dentry_page;
	struct f2fs_dir_entry *de = NULL;
	bool room = false;
	int max_slots;
	f2fs_hash_t namehash = f2fs_dentry_hash(dir, &name, fname);

	nbucket = dir_buckets(level, F2FS_I(dir)->i_dir_level);
	nblock = bucket_blocks(level);

	bidx = dir_block_index(level, F2FS_I(dir)->i_dir_level,
					le32_to_cpu(namehash) % nbucket);
	end_block = bidx + nblock;

	for (; bidx < end_block; bidx++) {
		/* no need to allocate new dentry pages to all the indices */
		dentry_page = f2fs_find_data_page(dir, bidx);
		if (IS_ERR(dentry_page)) {
			if (PTR_ERR(dentry_page) == -ENOENT) {
				room = true;
				continue;
			} else {
				*res_page = dentry_page;
				break;
			}
		}

		de = find_in_block(dir, dentry_page, fname, namehash,
							&max_slots, res_page);
		if (de)
			break;

		if (max_slots >= s)
			room = true;
		f2fs_put_page(dentry_page, 0);
	}

	if (!de && room && F2FS_I(dir)->chash != namehash) {
		F2FS_I(dir)->chash = namehash;
		F2FS_I(dir)->clevel = level;
	}

	return de;
}
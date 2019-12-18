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
struct fscrypt_str {int /*<<< orphan*/ * name; int /*<<< orphan*/  len; } ;
struct fscrypt_name {int /*<<< orphan*/  usr_fname; } ;
struct f2fs_dir_entry {int /*<<< orphan*/  name_len; } ;
struct f2fs_dentry_ptr {unsigned long max; struct f2fs_dir_entry* dentry; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  f2fs_hash_t ;

/* Variables and functions */
 scalar_t__ GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_fname_setup_ci_filename (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fscrypt_str*) ; 
 scalar_t__ f2fs_match_name (struct f2fs_dentry_ptr*,struct f2fs_dir_entry*,struct fscrypt_name*,struct fscrypt_str*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit_le (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct f2fs_dir_entry *f2fs_find_target_dentry(struct fscrypt_name *fname,
			f2fs_hash_t namehash, int *max_slots,
			struct f2fs_dentry_ptr *d)
{
	struct f2fs_dir_entry *de;
	struct fscrypt_str cf_str = { .name = NULL, .len = 0 };
	unsigned long bit_pos = 0;
	int max_len = 0;

#ifdef CONFIG_UNICODE
	f2fs_fname_setup_ci_filename(d->inode, fname->usr_fname, &cf_str);
#endif

	if (max_slots)
		*max_slots = 0;
	while (bit_pos < d->max) {
		if (!test_bit_le(bit_pos, d->bitmap)) {
			bit_pos++;
			max_len++;
			continue;
		}

		de = &d->dentry[bit_pos];

		if (unlikely(!de->name_len)) {
			bit_pos++;
			continue;
		}

		if (f2fs_match_name(d, de, fname, &cf_str, bit_pos, namehash))
			goto found;

		if (max_slots && max_len > *max_slots)
			*max_slots = max_len;
		max_len = 0;

		bit_pos += GET_DENTRY_SLOTS(le16_to_cpu(de->name_len));
	}

	de = NULL;
found:
	if (max_slots && max_len > *max_slots)
		*max_slots = max_len;

#ifdef CONFIG_UNICODE
	kvfree(cf_str.name);
#endif
	return de;
}
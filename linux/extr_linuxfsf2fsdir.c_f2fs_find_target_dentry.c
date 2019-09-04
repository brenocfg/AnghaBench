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
struct fscrypt_name {int dummy; } ;
struct f2fs_dir_entry {scalar_t__ hash_code; int /*<<< orphan*/  name_len; } ;
struct f2fs_dentry_ptr {unsigned long max; int /*<<< orphan*/ * filename; struct f2fs_dir_entry* dentry; int /*<<< orphan*/  bitmap; } ;
typedef  scalar_t__ f2fs_hash_t ;

/* Variables and functions */
 scalar_t__ GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 scalar_t__ fscrypt_match_name (struct fscrypt_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit_le (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct f2fs_dir_entry *f2fs_find_target_dentry(struct fscrypt_name *fname,
			f2fs_hash_t namehash, int *max_slots,
			struct f2fs_dentry_ptr *d)
{
	struct f2fs_dir_entry *de;
	unsigned long bit_pos = 0;
	int max_len = 0;

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

		if (de->hash_code == namehash &&
		    fscrypt_match_name(fname, d->filename[bit_pos],
				       le16_to_cpu(de->name_len)))
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
	return de;
}
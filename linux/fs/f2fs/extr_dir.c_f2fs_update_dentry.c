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
typedef  int /*<<< orphan*/  umode_t ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct f2fs_dir_entry {scalar_t__ name_len; int /*<<< orphan*/  ino; int /*<<< orphan*/  hash_code; } ;
struct f2fs_dentry_ptr {scalar_t__ bitmap; int /*<<< orphan*/ * filename; struct f2fs_dir_entry* dentry; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  int /*<<< orphan*/  f2fs_hash_t ;

/* Variables and functions */
 int GET_DENTRY_SLOTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit_le (unsigned int,void*) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_de_type (struct f2fs_dir_entry*,int /*<<< orphan*/ ) ; 

void f2fs_update_dentry(nid_t ino, umode_t mode, struct f2fs_dentry_ptr *d,
				const struct qstr *name, f2fs_hash_t name_hash,
				unsigned int bit_pos)
{
	struct f2fs_dir_entry *de;
	int slots = GET_DENTRY_SLOTS(name->len);
	int i;

	de = &d->dentry[bit_pos];
	de->hash_code = name_hash;
	de->name_len = cpu_to_le16(name->len);
	memcpy(d->filename[bit_pos], name->name, name->len);
	de->ino = cpu_to_le32(ino);
	set_de_type(de, mode);
	for (i = 0; i < slots; i++) {
		__set_bit_le(bit_pos + i, (void *)d->bitmap);
		/* avoid wrong garbage data for readdir */
		if (i)
			(de + i)->name_len = 0;
	}
}
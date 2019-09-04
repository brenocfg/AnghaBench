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
struct timespec64 {int dummy; } ;
struct qstr {int /*<<< orphan*/  name; } ;
struct msdos_dir_slot {int dummy; } ;
struct inode {struct timespec64 i_atime; struct timespec64 i_mtime; struct timespec64 i_ctime; } ;
struct fat_slot_info {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  MSDOS_SLOTS ; 
 int fat_add_entries (struct inode*,struct msdos_dir_slot*,int,struct fat_slot_info*) ; 
 int /*<<< orphan*/  fat_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct msdos_dir_slot*) ; 
 struct msdos_dir_slot* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int vfat_build_slots (struct inode*,int /*<<< orphan*/ ,unsigned int,int,int,struct timespec64*,struct msdos_dir_slot*,int*) ; 
 unsigned int vfat_striptail_len (struct qstr const*) ; 

__attribute__((used)) static int vfat_add_entry(struct inode *dir, const struct qstr *qname,
			  int is_dir, int cluster, struct timespec64 *ts,
			  struct fat_slot_info *sinfo)
{
	struct msdos_dir_slot *slots;
	unsigned int len;
	int err, nr_slots;

	len = vfat_striptail_len(qname);
	if (len == 0)
		return -ENOENT;

	slots = kmalloc_array(MSDOS_SLOTS, sizeof(*slots), GFP_NOFS);
	if (slots == NULL)
		return -ENOMEM;

	err = vfat_build_slots(dir, qname->name, len, is_dir, cluster, ts,
			       slots, &nr_slots);
	if (err)
		goto cleanup;

	err = fat_add_entries(dir, slots, nr_slots, sinfo);
	if (err)
		goto cleanup;

	/* update timestamp */
	dir->i_ctime = dir->i_mtime = dir->i_atime = *ts;
	if (IS_DIRSYNC(dir))
		(void)fat_sync_inode(dir);
	else
		mark_inode_dirty(dir);
cleanup:
	kfree(slots);
	return err;
}
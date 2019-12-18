#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Flags; } ;
union hfs_cat_rec {int type; TYPE_1__ file; } ;
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_ino; void* i_ctime; void* i_mtime; int /*<<< orphan*/  i_size; struct super_block* i_sb; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  bnode; int /*<<< orphan*/  search_key; int /*<<< orphan*/  entryoffset; TYPE_2__* tree; } ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_6__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_5__ {int depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAT_MOD ; 
 int EEXIST ; 
 int EIO ; 
 int ENOENT ; 
 int HFS_CDR_FIL ; 
 int /*<<< orphan*/  HFS_CDR_FTH ; 
 int /*<<< orphan*/  HFS_CDR_THD ; 
 int HFS_FIL_THD ; 
 TYPE_3__* HFS_SB (struct super_block*) ; 
 void* current_time (struct inode*) ; 
 int hfs_bmap_reserve (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hfs_bnode_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,union hfs_cat_rec*,int /*<<< orphan*/ ,int) ; 
 int hfs_brec_find (struct hfs_find_data*) ; 
 int hfs_brec_insert (struct hfs_find_data*,union hfs_cat_rec*,int) ; 
 int hfs_brec_remove (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_cat_build_key (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*) ; 
 int hfs_cat_build_thread (struct super_block*,union hfs_cat_rec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

int hfs_cat_move(u32 cnid, struct inode *src_dir, const struct qstr *src_name,
		 struct inode *dst_dir, const struct qstr *dst_name)
{
	struct super_block *sb;
	struct hfs_find_data src_fd, dst_fd;
	union hfs_cat_rec entry;
	int entry_size, type;
	int err;

	hfs_dbg(CAT_MOD, "rename_cat: %u - %lu,%s - %lu,%s\n",
		cnid, src_dir->i_ino, src_name->name,
		dst_dir->i_ino, dst_name->name);
	sb = src_dir->i_sb;
	err = hfs_find_init(HFS_SB(sb)->cat_tree, &src_fd);
	if (err)
		return err;
	dst_fd = src_fd;

	/*
	 * Fail early and avoid ENOSPC during the btree operations. We may
	 * have to split the root node at most once.
	 */
	err = hfs_bmap_reserve(src_fd.tree, 2 * src_fd.tree->depth);
	if (err)
		goto out;

	/* find the old dir entry and read the data */
	hfs_cat_build_key(sb, src_fd.search_key, src_dir->i_ino, src_name);
	err = hfs_brec_find(&src_fd);
	if (err)
		goto out;
	if (src_fd.entrylength > sizeof(entry) || src_fd.entrylength < 0) {
		err = -EIO;
		goto out;
	}

	hfs_bnode_read(src_fd.bnode, &entry, src_fd.entryoffset,
			    src_fd.entrylength);

	/* create new dir entry with the data from the old entry */
	hfs_cat_build_key(sb, dst_fd.search_key, dst_dir->i_ino, dst_name);
	err = hfs_brec_find(&dst_fd);
	if (err != -ENOENT) {
		if (!err)
			err = -EEXIST;
		goto out;
	}

	err = hfs_brec_insert(&dst_fd, &entry, src_fd.entrylength);
	if (err)
		goto out;
	dst_dir->i_size++;
	dst_dir->i_mtime = dst_dir->i_ctime = current_time(dst_dir);
	mark_inode_dirty(dst_dir);

	/* finally remove the old entry */
	hfs_cat_build_key(sb, src_fd.search_key, src_dir->i_ino, src_name);
	err = hfs_brec_find(&src_fd);
	if (err)
		goto out;
	err = hfs_brec_remove(&src_fd);
	if (err)
		goto out;
	src_dir->i_size--;
	src_dir->i_mtime = src_dir->i_ctime = current_time(src_dir);
	mark_inode_dirty(src_dir);

	type = entry.type;
	if (type == HFS_CDR_FIL && !(entry.file.Flags & HFS_FIL_THD))
		goto out;

	/* remove old thread entry */
	hfs_cat_build_key(sb, src_fd.search_key, cnid, NULL);
	err = hfs_brec_find(&src_fd);
	if (err)
		goto out;
	err = hfs_brec_remove(&src_fd);
	if (err)
		goto out;

	/* create new thread entry */
	hfs_cat_build_key(sb, dst_fd.search_key, cnid, NULL);
	entry_size = hfs_cat_build_thread(sb, &entry, type == HFS_CDR_FIL ? HFS_CDR_FTH : HFS_CDR_THD,
					dst_dir->i_ino, dst_name);
	err = hfs_brec_find(&dst_fd);
	if (err != -ENOENT) {
		if (!err)
			err = -EEXIST;
		goto out;
	}
	err = hfs_brec_insert(&dst_fd, &entry, entry_size);
out:
	hfs_bnode_put(dst_fd.bnode);
	hfs_find_exit(&src_fd);
	return err;
}
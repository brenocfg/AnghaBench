#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct qstr {int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_ino; void* i_ctime; void* i_mtime; int /*<<< orphan*/  i_size; struct super_block* i_sb; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  bnode; int /*<<< orphan*/  search_key; int /*<<< orphan*/  entryoffset; TYPE_5__* tree; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ hfsplus_cat_entry ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_9__ {int /*<<< orphan*/  cat_tree; } ;
struct TYPE_8__ {scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAT_MOD ; 
 int EEXIST ; 
 int EIO ; 
 int ENOENT ; 
 int HFSPLUS_FOLDER ; 
 int /*<<< orphan*/  HFSPLUS_I_CAT_DIRTY ; 
 TYPE_6__* HFSPLUS_SB (struct super_block*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* current_time (struct inode*) ; 
 int hfs_bmap_reserve (TYPE_5__*,int) ; 
 int /*<<< orphan*/  hfs_bnode_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int hfs_bnode_read_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hfs_brec_find (struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 int hfs_brec_insert (struct hfs_find_data*,TYPE_1__*,int) ; 
 int hfs_brec_remove (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_rec_by_key ; 
 int hfsplus_cat_build_key (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*) ; 
 int /*<<< orphan*/  hfsplus_cat_build_key_with_cnid (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hfsplus_fill_cat_thread (struct super_block*,TYPE_1__*,int,int /*<<< orphan*/ ,struct qstr const*) ; 
 int /*<<< orphan*/  hfsplus_mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsplus_subfolders_dec (struct inode*) ; 
 int /*<<< orphan*/  hfsplus_subfolders_inc (struct inode*) ; 
 scalar_t__ unlikely (int) ; 

int hfsplus_rename_cat(u32 cnid,
		       struct inode *src_dir, const struct qstr *src_name,
		       struct inode *dst_dir, const struct qstr *dst_name)
{
	struct super_block *sb = src_dir->i_sb;
	struct hfs_find_data src_fd, dst_fd;
	hfsplus_cat_entry entry;
	int entry_size, type;
	int err;

	hfs_dbg(CAT_MOD, "rename_cat: %u - %lu,%s - %lu,%s\n",
		cnid, src_dir->i_ino, src_name->name,
		dst_dir->i_ino, dst_name->name);
	err = hfs_find_init(HFSPLUS_SB(sb)->cat_tree, &src_fd);
	if (err)
		return err;
	dst_fd = src_fd;

	/*
	 * Fail early and avoid ENOSPC during the btree operations. We may
	 * have to split the root node at most twice.
	 */
	err = hfs_bmap_reserve(src_fd.tree, 4 * (int)src_fd.tree->depth - 1);
	if (err)
		goto out;

	/* find the old dir entry and read the data */
	err = hfsplus_cat_build_key(sb, src_fd.search_key,
			src_dir->i_ino, src_name);
	if (unlikely(err))
		goto out;

	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	if (err)
		goto out;
	if (src_fd.entrylength > sizeof(entry) || src_fd.entrylength < 0) {
		err = -EIO;
		goto out;
	}

	hfs_bnode_read(src_fd.bnode, &entry, src_fd.entryoffset,
				src_fd.entrylength);
	type = be16_to_cpu(entry.type);

	/* create new dir entry with the data from the old entry */
	err = hfsplus_cat_build_key(sb, dst_fd.search_key,
			dst_dir->i_ino, dst_name);
	if (unlikely(err))
		goto out;

	err = hfs_brec_find(&dst_fd, hfs_find_rec_by_key);
	if (err != -ENOENT) {
		if (!err)
			err = -EEXIST;
		goto out;
	}

	err = hfs_brec_insert(&dst_fd, &entry, src_fd.entrylength);
	if (err)
		goto out;
	dst_dir->i_size++;
	if (type == HFSPLUS_FOLDER)
		hfsplus_subfolders_inc(dst_dir);
	dst_dir->i_mtime = dst_dir->i_ctime = current_time(dst_dir);

	/* finally remove the old entry */
	err = hfsplus_cat_build_key(sb, src_fd.search_key,
			src_dir->i_ino, src_name);
	if (unlikely(err))
		goto out;

	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	if (err)
		goto out;
	err = hfs_brec_remove(&src_fd);
	if (err)
		goto out;
	src_dir->i_size--;
	if (type == HFSPLUS_FOLDER)
		hfsplus_subfolders_dec(src_dir);
	src_dir->i_mtime = src_dir->i_ctime = current_time(src_dir);

	/* remove old thread entry */
	hfsplus_cat_build_key_with_cnid(sb, src_fd.search_key, cnid);
	err = hfs_brec_find(&src_fd, hfs_find_rec_by_key);
	if (err)
		goto out;
	type = hfs_bnode_read_u16(src_fd.bnode, src_fd.entryoffset);
	err = hfs_brec_remove(&src_fd);
	if (err)
		goto out;

	/* create new thread entry */
	hfsplus_cat_build_key_with_cnid(sb, dst_fd.search_key, cnid);
	entry_size = hfsplus_fill_cat_thread(sb, &entry, type,
		dst_dir->i_ino, dst_name);
	if (unlikely(entry_size < 0)) {
		err = entry_size;
		goto out;
	}

	err = hfs_brec_find(&dst_fd, hfs_find_rec_by_key);
	if (err != -ENOENT) {
		if (!err)
			err = -EEXIST;
		goto out;
	}
	err = hfs_brec_insert(&dst_fd, &entry, entry_size);

	hfsplus_mark_inode_dirty(dst_dir, HFSPLUS_I_CAT_DIRTY);
	hfsplus_mark_inode_dirty(src_dir, HFSPLUS_I_CAT_DIRTY);
out:
	hfs_bnode_put(dst_fd.bnode);
	hfs_find_exit(&src_fd);
	return err;
}
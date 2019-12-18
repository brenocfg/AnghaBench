#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; scalar_t__ i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_8__ {int rootflags; int userflags; } ;
struct hfsplus_cat_folder {int flags; void* subfolders; void* valence; void* attribute_mod_date; void* content_mod_date; void* access_date; TYPE_2__ permissions; } ;
struct hfsplus_cat_file {int flags; void* attribute_mod_date; void* content_mod_date; void* access_date; TYPE_2__ permissions; int /*<<< orphan*/  data_fork; int /*<<< orphan*/  rsrc_fork; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; } ;
struct TYPE_7__ {struct hfsplus_cat_file file; struct hfsplus_cat_folder folder; } ;
typedef  TYPE_1__ hfsplus_cat_entry ;
struct TYPE_10__ {int /*<<< orphan*/  flags; scalar_t__ subfolders; struct inode* rsrc_inode; } ;
struct TYPE_9__ {int /*<<< orphan*/  cat_tree; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HFSPLUS_FILE_LOCKED ; 
 int HFSPLUS_FLG_IMMUTABLE ; 
 int /*<<< orphan*/  HFSPLUS_HAS_FOLDER_COUNT ; 
 TYPE_6__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 int /*<<< orphan*/  HFSPLUS_I_CAT_DIRTY ; 
 TYPE_5__* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_bnode_write (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 scalar_t__ hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 void* hfsp_ut2mt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsplus_cat_set_perms (struct inode*,TYPE_2__*) ; 
 scalar_t__ hfsplus_find_cat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfsplus_inode_write_fork (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hfsplus_cat_write_inode(struct inode *inode)
{
	struct inode *main_inode = inode;
	struct hfs_find_data fd;
	hfsplus_cat_entry entry;

	if (HFSPLUS_IS_RSRC(inode))
		main_inode = HFSPLUS_I(inode)->rsrc_inode;

	if (!main_inode->i_nlink)
		return 0;

	if (hfs_find_init(HFSPLUS_SB(main_inode->i_sb)->cat_tree, &fd))
		/* panic? */
		return -EIO;

	if (hfsplus_find_cat(main_inode->i_sb, main_inode->i_ino, &fd))
		/* panic? */
		goto out;

	if (S_ISDIR(main_inode->i_mode)) {
		struct hfsplus_cat_folder *folder = &entry.folder;

		if (fd.entrylength < sizeof(struct hfsplus_cat_folder))
			/* panic? */;
		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
					sizeof(struct hfsplus_cat_folder));
		/* simple node checks? */
		hfsplus_cat_set_perms(inode, &folder->permissions);
		folder->access_date = hfsp_ut2mt(inode->i_atime);
		folder->content_mod_date = hfsp_ut2mt(inode->i_mtime);
		folder->attribute_mod_date = hfsp_ut2mt(inode->i_ctime);
		folder->valence = cpu_to_be32(inode->i_size - 2);
		if (folder->flags & cpu_to_be16(HFSPLUS_HAS_FOLDER_COUNT)) {
			folder->subfolders =
				cpu_to_be32(HFSPLUS_I(inode)->subfolders);
		}
		hfs_bnode_write(fd.bnode, &entry, fd.entryoffset,
					 sizeof(struct hfsplus_cat_folder));
	} else if (HFSPLUS_IS_RSRC(inode)) {
		struct hfsplus_cat_file *file = &entry.file;
		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
			       sizeof(struct hfsplus_cat_file));
		hfsplus_inode_write_fork(inode, &file->rsrc_fork);
		hfs_bnode_write(fd.bnode, &entry, fd.entryoffset,
				sizeof(struct hfsplus_cat_file));
	} else {
		struct hfsplus_cat_file *file = &entry.file;

		if (fd.entrylength < sizeof(struct hfsplus_cat_file))
			/* panic? */;
		hfs_bnode_read(fd.bnode, &entry, fd.entryoffset,
					sizeof(struct hfsplus_cat_file));
		hfsplus_inode_write_fork(inode, &file->data_fork);
		hfsplus_cat_set_perms(inode, &file->permissions);
		if (HFSPLUS_FLG_IMMUTABLE &
				(file->permissions.rootflags |
					file->permissions.userflags))
			file->flags |= cpu_to_be16(HFSPLUS_FILE_LOCKED);
		else
			file->flags &= cpu_to_be16(~HFSPLUS_FILE_LOCKED);
		file->access_date = hfsp_ut2mt(inode->i_atime);
		file->content_mod_date = hfsp_ut2mt(inode->i_mtime);
		file->attribute_mod_date = hfsp_ut2mt(inode->i_ctime);
		hfs_bnode_write(fd.bnode, &entry, fd.entryoffset,
					 sizeof(struct hfsplus_cat_file));
	}

	set_bit(HFSPLUS_I_CAT_DIRTY, &HFSPLUS_I(inode)->flags);
out:
	hfs_find_exit(&fd);
	return 0;
}
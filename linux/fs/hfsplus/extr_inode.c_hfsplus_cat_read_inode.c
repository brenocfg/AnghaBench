#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct inode {int i_size; void* i_ctime; void* i_mtime; void* i_atime; int /*<<< orphan*/  i_mode; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; } ;
struct TYPE_8__ {scalar_t__ dev; } ;
struct hfsplus_cat_folder {int flags; scalar_t__ subfolders; int /*<<< orphan*/  create_date; int /*<<< orphan*/  attribute_mod_date; int /*<<< orphan*/  content_mod_date; int /*<<< orphan*/  access_date; scalar_t__ valence; TYPE_3__ permissions; } ;
struct hfsplus_cat_file {int /*<<< orphan*/  create_date; int /*<<< orphan*/  attribute_mod_date; int /*<<< orphan*/  content_mod_date; int /*<<< orphan*/  access_date; TYPE_3__ permissions; int /*<<< orphan*/  data_fork; int /*<<< orphan*/  rsrc_fork; } ;
struct hfs_find_data {int entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; } ;
struct TYPE_7__ {struct hfsplus_cat_file file; struct hfsplus_cat_folder folder; } ;
typedef  TYPE_2__ hfsplus_cat_entry ;
struct TYPE_9__ {int subfolders; int /*<<< orphan*/  create_date; scalar_t__ fs_blocks; scalar_t__ linkid; } ;
struct TYPE_6__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HFSPLUS_FILE ; 
 scalar_t__ HFSPLUS_FOLDER ; 
 int /*<<< orphan*/  HFSPLUS_HAS_FOLDER_COUNT ; 
 TYPE_5__* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (scalar_t__) ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_bnode_read (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hfs_bnode_read_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsp_mt2ut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsplus_aops ; 
 int /*<<< orphan*/  hfsplus_dir_inode_operations ; 
 int /*<<< orphan*/  hfsplus_dir_operations ; 
 int /*<<< orphan*/  hfsplus_file_inode_operations ; 
 int /*<<< orphan*/  hfsplus_file_operations ; 
 int /*<<< orphan*/  hfsplus_get_perms (struct inode*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  hfsplus_inode_read_fork (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  page_symlink_inode_operations ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 void* timespec_to_timespec64 (int /*<<< orphan*/ ) ; 

int hfsplus_cat_read_inode(struct inode *inode, struct hfs_find_data *fd)
{
	hfsplus_cat_entry entry;
	int res = 0;
	u16 type;

	type = hfs_bnode_read_u16(fd->bnode, fd->entryoffset);

	HFSPLUS_I(inode)->linkid = 0;
	if (type == HFSPLUS_FOLDER) {
		struct hfsplus_cat_folder *folder = &entry.folder;

		if (fd->entrylength < sizeof(struct hfsplus_cat_folder))
			/* panic? */;
		hfs_bnode_read(fd->bnode, &entry, fd->entryoffset,
					sizeof(struct hfsplus_cat_folder));
		hfsplus_get_perms(inode, &folder->permissions, 1);
		set_nlink(inode, 1);
		inode->i_size = 2 + be32_to_cpu(folder->valence);
		inode->i_atime = timespec_to_timespec64(hfsp_mt2ut(folder->access_date));
		inode->i_mtime = timespec_to_timespec64(hfsp_mt2ut(folder->content_mod_date));
		inode->i_ctime = timespec_to_timespec64(hfsp_mt2ut(folder->attribute_mod_date));
		HFSPLUS_I(inode)->create_date = folder->create_date;
		HFSPLUS_I(inode)->fs_blocks = 0;
		if (folder->flags & cpu_to_be16(HFSPLUS_HAS_FOLDER_COUNT)) {
			HFSPLUS_I(inode)->subfolders =
				be32_to_cpu(folder->subfolders);
		}
		inode->i_op = &hfsplus_dir_inode_operations;
		inode->i_fop = &hfsplus_dir_operations;
	} else if (type == HFSPLUS_FILE) {
		struct hfsplus_cat_file *file = &entry.file;

		if (fd->entrylength < sizeof(struct hfsplus_cat_file))
			/* panic? */;
		hfs_bnode_read(fd->bnode, &entry, fd->entryoffset,
					sizeof(struct hfsplus_cat_file));

		hfsplus_inode_read_fork(inode, HFSPLUS_IS_RSRC(inode) ?
					&file->rsrc_fork : &file->data_fork);
		hfsplus_get_perms(inode, &file->permissions, 0);
		set_nlink(inode, 1);
		if (S_ISREG(inode->i_mode)) {
			if (file->permissions.dev)
				set_nlink(inode,
					  be32_to_cpu(file->permissions.dev));
			inode->i_op = &hfsplus_file_inode_operations;
			inode->i_fop = &hfsplus_file_operations;
			inode->i_mapping->a_ops = &hfsplus_aops;
		} else if (S_ISLNK(inode->i_mode)) {
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &hfsplus_aops;
		} else {
			init_special_inode(inode, inode->i_mode,
					   be32_to_cpu(file->permissions.dev));
		}
		inode->i_atime = timespec_to_timespec64(hfsp_mt2ut(file->access_date));
		inode->i_mtime = timespec_to_timespec64(hfsp_mt2ut(file->content_mod_date));
		inode->i_ctime = timespec_to_timespec64(hfsp_mt2ut(file->attribute_mod_date));
		HFSPLUS_I(inode)->create_date = file->create_date;
	} else {
		pr_err("bad catalog entry used to create inode\n");
		res = -EIO;
	}
	return res;
}
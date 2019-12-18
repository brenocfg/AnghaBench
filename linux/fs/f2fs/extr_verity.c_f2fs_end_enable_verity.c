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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct fsverity_descriptor_location {int /*<<< orphan*/  pos; int /*<<< orphan*/  size; int /*<<< orphan*/  version; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  dloc ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_XATTR_INDEX_VERITY ; 
 int /*<<< orphan*/  F2FS_XATTR_NAME_VERITY ; 
 int /*<<< orphan*/  FI_VERITY_IN_PROGRESS ; 
 int /*<<< orphan*/  XATTR_CREATE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_set_inode_flags (struct inode*) ; 
 int f2fs_setxattr (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fsverity_descriptor_location*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_truncate (struct inode*) ; 
 scalar_t__ f2fs_verity_metadata_pos (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  file_set_verity (struct inode*) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int pagecache_write (struct inode*,void const*,size_t,scalar_t__) ; 

__attribute__((used)) static int f2fs_end_enable_verity(struct file *filp, const void *desc,
				  size_t desc_size, u64 merkle_tree_size)
{
	struct inode *inode = file_inode(filp);
	u64 desc_pos = f2fs_verity_metadata_pos(inode) + merkle_tree_size;
	struct fsverity_descriptor_location dloc = {
		.version = cpu_to_le32(1),
		.size = cpu_to_le32(desc_size),
		.pos = cpu_to_le64(desc_pos),
	};
	int err = 0;

	if (desc != NULL) {
		/* Succeeded; write the verity descriptor. */
		err = pagecache_write(inode, desc, desc_size, desc_pos);

		/* Write all pages before clearing FI_VERITY_IN_PROGRESS. */
		if (!err)
			err = filemap_write_and_wait(inode->i_mapping);
	}

	/* If we failed, truncate anything we wrote past i_size. */
	if (desc == NULL || err)
		f2fs_truncate(inode);

	clear_inode_flag(inode, FI_VERITY_IN_PROGRESS);

	if (desc != NULL && !err) {
		err = f2fs_setxattr(inode, F2FS_XATTR_INDEX_VERITY,
				    F2FS_XATTR_NAME_VERITY, &dloc, sizeof(dloc),
				    NULL, XATTR_CREATE);
		if (!err) {
			file_set_verity(inode);
			f2fs_set_inode_flags(inode);
			f2fs_mark_inode_dirty_sync(inode, true);
		}
	}
	return err;
}
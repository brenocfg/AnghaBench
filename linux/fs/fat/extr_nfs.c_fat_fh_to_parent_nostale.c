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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct fid {int dummy; } ;
struct fat_fid {int parent_i_pos_hi; int parent_i_pos_low; int /*<<< orphan*/  parent_i_gen; } ;
struct dentry {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int FAT_FID_SIZE_WITH_PARENT ; 
#define  FILEID_FAT_WITH_PARENT 128 
 struct inode* __fat_nfs_get_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 

__attribute__((used)) static struct dentry *fat_fh_to_parent_nostale(struct super_block *sb,
					       struct fid *fh, int fh_len,
					       int fh_type)
{
	struct inode *inode = NULL;
	struct fat_fid *fid = (struct fat_fid *)fh;
	loff_t i_pos;

	if (fh_len < FAT_FID_SIZE_WITH_PARENT)
		return NULL;

	switch (fh_type) {
	case FILEID_FAT_WITH_PARENT:
		i_pos = fid->parent_i_pos_hi;
		i_pos = (i_pos << 32) | (fid->parent_i_pos_low);
		inode = __fat_nfs_get_inode(sb, 0, fid->parent_i_gen, i_pos);
		break;
	}

	return d_obtain_alias(inode);
}
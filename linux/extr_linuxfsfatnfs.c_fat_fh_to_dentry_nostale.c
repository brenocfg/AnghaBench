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
struct fat_fid {int i_pos_hi; int i_pos_low; int /*<<< orphan*/  i_gen; } ;
struct dentry {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int FAT_FID_SIZE_WITHOUT_PARENT ; 
 int FAT_FID_SIZE_WITH_PARENT ; 
#define  FILEID_FAT_WITHOUT_PARENT 129 
#define  FILEID_FAT_WITH_PARENT 128 
 struct inode* __fat_nfs_get_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 

__attribute__((used)) static struct dentry *fat_fh_to_dentry_nostale(struct super_block *sb,
					       struct fid *fh, int fh_len,
					       int fh_type)
{
	struct inode *inode = NULL;
	struct fat_fid *fid = (struct fat_fid *)fh;
	loff_t i_pos;

	switch (fh_type) {
	case FILEID_FAT_WITHOUT_PARENT:
		if (fh_len < FAT_FID_SIZE_WITHOUT_PARENT)
			return NULL;
		break;
	case FILEID_FAT_WITH_PARENT:
		if (fh_len < FAT_FID_SIZE_WITH_PARENT)
			return NULL;
		break;
	default:
		return NULL;
	}
	i_pos = fid->i_pos_hi;
	i_pos = (i_pos << 32) | (fid->i_pos_low);
	inode = __fat_nfs_get_inode(sb, 0, fid->i_gen, i_pos);

	return d_obtain_alias(inode);
}
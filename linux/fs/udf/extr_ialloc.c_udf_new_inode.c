#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  udf_pblk_t ;
struct udf_sb_info {scalar_t__ s_udfrev; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; int /*<<< orphan*/  s_alloc_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct TYPE_3__ {void* i_data; } ;
struct udf_inode_info {int i_efe; int i_checkpoint; int /*<<< orphan*/  i_crtime; int /*<<< orphan*/  i_alloc_type; int /*<<< orphan*/  i_extraPerms; scalar_t__ i_use; scalar_t__ i_lenAlloc; scalar_t__ i_lenEAttr; TYPE_2__ i_location; int /*<<< orphan*/  i_unique; TYPE_1__ i_ext; } ;
struct super_block {scalar_t__ s_blocksize; } ;
struct logicalVolIntegrityDescImpUse {int /*<<< orphan*/  numFiles; int /*<<< orphan*/  numDirs; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; struct super_block* i_sb; scalar_t__ i_blocks; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_generation; } ;
struct fileEntry {int dummy; } ;
struct extendedFileEntry {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  FE_PERM_U_CHATTR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_LONG ; 
 int /*<<< orphan*/  ICBTAG_FLAG_AD_SHORT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDF_FLAG_GID_SET ; 
 int /*<<< orphan*/  UDF_FLAG_UID_SET ; 
 int /*<<< orphan*/  UDF_FLAG_USE_AD_IN_ICB ; 
 int /*<<< orphan*/  UDF_FLAG_USE_EXTENDED_FE ; 
 int /*<<< orphan*/  UDF_FLAG_USE_SHORT_AD ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 scalar_t__ UDF_VERS_USE_EXTENDED_FE ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_inode_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lvid_get_unique_id (struct super_block*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  udf_get_lb_pblock (struct super_block*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_new_block (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct super_block*) ; 
 int /*<<< orphan*/  udf_update_extra_perms (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 
 scalar_t__ unlikely (int) ; 

struct inode *udf_new_inode(struct inode *dir, umode_t mode)
{
	struct super_block *sb = dir->i_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct inode *inode;
	udf_pblk_t block;
	uint32_t start = UDF_I(dir)->i_location.logicalBlockNum;
	struct udf_inode_info *iinfo;
	struct udf_inode_info *dinfo = UDF_I(dir);
	struct logicalVolIntegrityDescImpUse *lvidiu;
	int err;

	inode = new_inode(sb);

	if (!inode)
		return ERR_PTR(-ENOMEM);

	iinfo = UDF_I(inode);
	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_EXTENDED_FE)) {
		iinfo->i_efe = 1;
		if (UDF_VERS_USE_EXTENDED_FE > sbi->s_udfrev)
			sbi->s_udfrev = UDF_VERS_USE_EXTENDED_FE;
		iinfo->i_ext.i_data = kzalloc(inode->i_sb->s_blocksize -
					    sizeof(struct extendedFileEntry),
					    GFP_KERNEL);
	} else {
		iinfo->i_efe = 0;
		iinfo->i_ext.i_data = kzalloc(inode->i_sb->s_blocksize -
					    sizeof(struct fileEntry),
					    GFP_KERNEL);
	}
	if (!iinfo->i_ext.i_data) {
		iput(inode);
		return ERR_PTR(-ENOMEM);
	}

	err = -ENOSPC;
	block = udf_new_block(dir->i_sb, NULL,
			      dinfo->i_location.partitionReferenceNum,
			      start, &err);
	if (err) {
		iput(inode);
		return ERR_PTR(err);
	}

	lvidiu = udf_sb_lvidiu(sb);
	if (lvidiu) {
		iinfo->i_unique = lvid_get_unique_id(sb);
		inode->i_generation = iinfo->i_unique;
		mutex_lock(&sbi->s_alloc_mutex);
		if (S_ISDIR(mode))
			le32_add_cpu(&lvidiu->numDirs, 1);
		else
			le32_add_cpu(&lvidiu->numFiles, 1);
		udf_updated_lvid(sb);
		mutex_unlock(&sbi->s_alloc_mutex);
	}

	inode_init_owner(inode, dir, mode);
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_UID_SET))
		inode->i_uid = sbi->s_uid;
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_GID_SET))
		inode->i_gid = sbi->s_gid;

	iinfo->i_location.logicalBlockNum = block;
	iinfo->i_location.partitionReferenceNum =
				dinfo->i_location.partitionReferenceNum;
	inode->i_ino = udf_get_lb_pblock(sb, &iinfo->i_location, 0);
	inode->i_blocks = 0;
	iinfo->i_lenEAttr = 0;
	iinfo->i_lenAlloc = 0;
	iinfo->i_use = 0;
	iinfo->i_checkpoint = 1;
	iinfo->i_extraPerms = FE_PERM_U_CHATTR;
	udf_update_extra_perms(inode, mode);

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_AD_IN_ICB))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_IN_ICB;
	else if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_USE_SHORT_AD))
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_SHORT;
	else
		iinfo->i_alloc_type = ICBTAG_FLAG_AD_LONG;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	iinfo->i_crtime = inode->i_mtime;
	if (unlikely(insert_inode_locked(inode) < 0)) {
		make_bad_inode(inode);
		iput(inode);
		return ERR_PTR(-EIO);
	}
	mark_inode_dirty(inode);

	return inode;
}
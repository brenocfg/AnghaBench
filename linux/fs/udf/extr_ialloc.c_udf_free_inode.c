#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; } ;
struct super_block {int dummy; } ;
struct logicalVolIntegrityDescImpUse {int /*<<< orphan*/  numFiles; int /*<<< orphan*/  numDirs; } ;
struct inode {int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_location; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_free_blocks (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct super_block*) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 

void udf_free_inode(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct logicalVolIntegrityDescImpUse *lvidiu = udf_sb_lvidiu(sb);

	if (lvidiu) {
		mutex_lock(&sbi->s_alloc_mutex);
		if (S_ISDIR(inode->i_mode))
			le32_add_cpu(&lvidiu->numDirs, -1);
		else
			le32_add_cpu(&lvidiu->numFiles, -1);
		udf_updated_lvid(sb);
		mutex_unlock(&sbi->s_alloc_mutex);
	}

	udf_free_blocks(sb, NULL, &UDF_I(inode)->i_location, 0, 1);
}
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
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; scalar_t__ s_lvid_dirty; struct buffer_head* s_lvid_bh; } ;
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * identSuffix; } ;
struct logicalVolIntegrityDescImpUse {TYPE_1__ impIdent; } ;
struct logicalVolIntegrityDesc {int /*<<< orphan*/  integrityType; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ LVID_INTEGRITY_TYPE_CLOSE ; 
 int /*<<< orphan*/  LVID_INTEGRITY_TYPE_OPEN ; 
 int /*<<< orphan*/  UDF_FLAG_INCONSISTENT ; 
 int /*<<< orphan*/  UDF_OS_CLASS_UNIX ; 
 int /*<<< orphan*/  UDF_OS_ID_LINUX ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  udf_finalize_lvid (struct logicalVolIntegrityDesc*) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct super_block*) ; 

__attribute__((used)) static void udf_open_lvid(struct super_block *sb)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct buffer_head *bh = sbi->s_lvid_bh;
	struct logicalVolIntegrityDesc *lvid;
	struct logicalVolIntegrityDescImpUse *lvidiu;

	if (!bh)
		return;
	lvid = (struct logicalVolIntegrityDesc *)bh->b_data;
	lvidiu = udf_sb_lvidiu(sb);
	if (!lvidiu)
		return;

	mutex_lock(&sbi->s_alloc_mutex);
	lvidiu->impIdent.identSuffix[0] = UDF_OS_CLASS_UNIX;
	lvidiu->impIdent.identSuffix[1] = UDF_OS_ID_LINUX;
	if (le32_to_cpu(lvid->integrityType) == LVID_INTEGRITY_TYPE_CLOSE)
		lvid->integrityType = cpu_to_le32(LVID_INTEGRITY_TYPE_OPEN);
	else
		UDF_SET_FLAG(sb, UDF_FLAG_INCONSISTENT);

	udf_finalize_lvid(lvid);
	mark_buffer_dirty(bh);
	sbi->s_lvid_dirty = 0;
	mutex_unlock(&sbi->s_alloc_mutex);
	/* Make opening of filesystem visible on the media immediately */
	sync_dirty_buffer(bh);
}
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
typedef  int u64 ;
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; struct buffer_head* s_lvid_bh; } ;
struct super_block {int dummy; } ;
struct logicalVolIntegrityDesc {scalar_t__ logicalVolContentsUse; } ;
struct logicalVolHeaderDesc {int /*<<< orphan*/  uniqueID; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_updated_lvid (struct super_block*) ; 

u64 lvid_get_unique_id(struct super_block *sb)
{
	struct buffer_head *bh;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct logicalVolIntegrityDesc *lvid;
	struct logicalVolHeaderDesc *lvhd;
	u64 uniqueID;
	u64 ret;

	bh = sbi->s_lvid_bh;
	if (!bh)
		return 0;

	lvid = (struct logicalVolIntegrityDesc *)bh->b_data;
	lvhd = (struct logicalVolHeaderDesc *)lvid->logicalVolContentsUse;

	mutex_lock(&sbi->s_alloc_mutex);
	ret = uniqueID = le64_to_cpu(lvhd->uniqueID);
	if (!(++uniqueID & 0xFFFFFFFF))
		uniqueID += 16;
	lvhd->uniqueID = cpu_to_le64(uniqueID);
	udf_updated_lvid(sb);
	mutex_unlock(&sbi->s_alloc_mutex);

	return ret;
}
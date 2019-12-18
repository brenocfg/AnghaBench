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
struct udf_sb_info {int /*<<< orphan*/  s_last_block; } ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  UDF_CLEAR_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDF_FLAG_VARCONV ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  UDF_SET_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 int udf_scan_anchors (struct super_block*,int /*<<< orphan*/ *,struct kernel_lb_addr*) ; 
 int /*<<< orphan*/  udf_variable_to_fixed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_find_anchor(struct super_block *sb,
			   struct kernel_lb_addr *fileset)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	sector_t lastblock = sbi->s_last_block;
	int ret;

	ret = udf_scan_anchors(sb, &lastblock, fileset);
	if (ret != -EAGAIN)
		goto out;

	/* No anchor found? Try VARCONV conversion of block numbers */
	UDF_SET_FLAG(sb, UDF_FLAG_VARCONV);
	lastblock = udf_variable_to_fixed(sbi->s_last_block);
	/* Firstly, we try to not convert number of the last block */
	ret = udf_scan_anchors(sb, &lastblock, fileset);
	if (ret != -EAGAIN)
		goto out;

	lastblock = sbi->s_last_block;
	/* Secondly, we try with converted number of the last block */
	ret = udf_scan_anchors(sb, &lastblock, fileset);
	if (ret < 0) {
		/* VARCONV didn't help. Clear it. */
		UDF_CLEAR_FLAG(sb, UDF_FLAG_VARCONV);
	}
out:
	if (ret == 0)
		sbi->s_last_block = lastblock;
	return ret;
}
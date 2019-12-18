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
struct udf_sb_info {int /*<<< orphan*/  s_anchor; scalar_t__ s_last_block; } ;
struct udf_options {int /*<<< orphan*/  anchor; int /*<<< orphan*/  novrs; scalar_t__ lastblock; int /*<<< orphan*/  blocksize; } ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  VSD_FIRST_SECTOR_OFFSET ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 int udf_check_vsd (struct super_block*) ; 
 int /*<<< orphan*/  udf_debug (char*,...) ; 
 int udf_find_anchor (struct super_block*,struct kernel_lb_addr*) ; 
 scalar_t__ udf_get_last_block (struct super_block*) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*) ; 

__attribute__((used)) static int udf_load_vrs(struct super_block *sb, struct udf_options *uopt,
			int silent, struct kernel_lb_addr *fileset)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	int nsr = 0;
	int ret;

	if (!sb_set_blocksize(sb, uopt->blocksize)) {
		if (!silent)
			udf_warn(sb, "Bad block size\n");
		return -EINVAL;
	}
	sbi->s_last_block = uopt->lastblock;
	if (!uopt->novrs) {
		/* Check that it is NSR02 compliant */
		nsr = udf_check_vsd(sb);
		if (!nsr) {
			if (!silent)
				udf_warn(sb, "No VRS found\n");
			return -EINVAL;
		}
		if (nsr == -1)
			udf_debug("Failed to read sector at offset %d. "
				  "Assuming open disc. Skipping validity "
				  "check\n", VSD_FIRST_SECTOR_OFFSET);
		if (!sbi->s_last_block)
			sbi->s_last_block = udf_get_last_block(sb);
	} else {
		udf_debug("Validity check skipped because of novrs option\n");
	}

	/* Look for anchor block and load Volume Descriptor Sequence */
	sbi->s_anchor = uopt->anchor;
	ret = udf_find_anchor(sb, fileset);
	if (ret < 0) {
		if (!silent && ret == -EAGAIN)
			udf_warn(sb, "No anchor found\n");
		return ret;
	}
	return 0;
}
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
typedef  scalar_t__ uint16_t ;
struct udf_sb_info {struct buffer_head* s_lvid_bh; } ;
struct super_block {scalar_t__ s_blocksize; } ;
struct TYPE_2__ {scalar_t__ extLength; } ;
struct logicalVolIntegrityDesc {TYPE_1__ nextIntegrityExt; } ;
struct kernel_extent_ad {scalar_t__ extLength; int /*<<< orphan*/  extLocation; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ TAG_IDENT_LVID ; 
 int UDF_MAX_LVID_NESTING ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct kernel_extent_ad leea_to_cpu (TYPE_1__) ; 
 struct buffer_head* udf_read_tagged (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*,int) ; 

__attribute__((used)) static void udf_load_logicalvolint(struct super_block *sb, struct kernel_extent_ad loc)
{
	struct buffer_head *bh, *final_bh;
	uint16_t ident;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct logicalVolIntegrityDesc *lvid;
	int indirections = 0;

	while (++indirections <= UDF_MAX_LVID_NESTING) {
		final_bh = NULL;
		while (loc.extLength > 0 &&
			(bh = udf_read_tagged(sb, loc.extLocation,
					loc.extLocation, &ident))) {
			if (ident != TAG_IDENT_LVID) {
				brelse(bh);
				break;
			}

			brelse(final_bh);
			final_bh = bh;

			loc.extLength -= sb->s_blocksize;
			loc.extLocation++;
		}

		if (!final_bh)
			return;

		brelse(sbi->s_lvid_bh);
		sbi->s_lvid_bh = final_bh;

		lvid = (struct logicalVolIntegrityDesc *)final_bh->b_data;
		if (lvid->nextIntegrityExt.extLength == 0)
			return;

		loc = leea_to_cpu(lvid->nextIntegrityExt);
	}

	udf_warn(sb, "Too many LVID indirections (max %u), ignoring.\n",
		UDF_MAX_LVID_NESTING);
	brelse(sbi->s_lvid_bh);
	sbi->s_lvid_bh = NULL;
}
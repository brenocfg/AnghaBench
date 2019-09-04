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
struct super_block {int dummy; } ;
struct ext2_sb_info {int s_desc_per_block; TYPE_1__* s_es; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_first_meta_bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_FEATURE_INCOMPAT_META_BG ; 
 int /*<<< orphan*/  EXT2_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 scalar_t__ ext2_bg_has_super (struct super_block*,unsigned long) ; 
 unsigned long ext2_group_first_block_no (struct super_block*,unsigned long) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long descriptor_loc(struct super_block *sb,
				    unsigned long logic_sb_block,
				    int nr)
{
	struct ext2_sb_info *sbi = EXT2_SB(sb);
	unsigned long bg, first_meta_bg;
	int has_super = 0;
	
	first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

	if (!EXT2_HAS_INCOMPAT_FEATURE(sb, EXT2_FEATURE_INCOMPAT_META_BG) ||
	    nr < first_meta_bg)
		return (logic_sb_block + nr + 1);
	bg = sbi->s_desc_per_block * nr;
	if (ext2_bg_has_super(sb, bg))
		has_super = 1;

	return ext2_group_first_block_no(sb, bg) + has_super;
}
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
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int /*<<< orphan*/  sit_base_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ssa_blkaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DATA_GENERIC 136 
#define  DATA_GENERIC_ENHANCE 135 
#define  DATA_GENERIC_ENHANCE_READ 134 
 int /*<<< orphan*/  MAIN_BLKADDR (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  MAX_BLKADDR (struct f2fs_sb_info*) ; 
#define  META_CP 133 
#define  META_GENERIC 132 
#define  META_NAT 131 
#define  META_POR 130 
#define  META_SIT 129 
#define  META_SSA 128 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 int /*<<< orphan*/  SEG0_BLKADDR (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  SIT_BLK_CNT (struct f2fs_sb_info*) ; 
 TYPE_2__* SIT_I (struct f2fs_sb_info*) ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __is_bitmap_valid (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __start_cp_addr (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_warn (struct f2fs_sb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlikely (int) ; 

bool f2fs_is_valid_blkaddr(struct f2fs_sb_info *sbi,
					block_t blkaddr, int type)
{
	switch (type) {
	case META_NAT:
		break;
	case META_SIT:
		if (unlikely(blkaddr >= SIT_BLK_CNT(sbi)))
			return false;
		break;
	case META_SSA:
		if (unlikely(blkaddr >= MAIN_BLKADDR(sbi) ||
			blkaddr < SM_I(sbi)->ssa_blkaddr))
			return false;
		break;
	case META_CP:
		if (unlikely(blkaddr >= SIT_I(sbi)->sit_base_addr ||
			blkaddr < __start_cp_addr(sbi)))
			return false;
		break;
	case META_POR:
		if (unlikely(blkaddr >= MAX_BLKADDR(sbi) ||
			blkaddr < MAIN_BLKADDR(sbi)))
			return false;
		break;
	case DATA_GENERIC:
	case DATA_GENERIC_ENHANCE:
	case DATA_GENERIC_ENHANCE_READ:
		if (unlikely(blkaddr >= MAX_BLKADDR(sbi) ||
				blkaddr < MAIN_BLKADDR(sbi))) {
			f2fs_warn(sbi, "access invalid blkaddr:%u",
				  blkaddr);
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			WARN_ON(1);
			return false;
		} else {
			return __is_bitmap_valid(sbi, blkaddr, type);
		}
		break;
	case META_GENERIC:
		if (unlikely(blkaddr < SEG0_BLKADDR(sbi) ||
			blkaddr >= MAIN_BLKADDR(sbi)))
			return false;
		break;
	default:
		BUG();
	}

	return true;
}
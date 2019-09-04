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
struct f2fs_sb_info {int cur_cp_pack; scalar_t__ blocks_per_seg; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_2__ {int /*<<< orphan*/  cp_blkaddr; } ;

/* Variables and functions */
 TYPE_1__* F2FS_RAW_SUPER (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline block_t __start_cp_next_addr(struct f2fs_sb_info *sbi)
{
	block_t start_addr = le32_to_cpu(F2FS_RAW_SUPER(sbi)->cp_blkaddr);

	if (sbi->cur_cp_pack == 1)
		start_addr += sbi->blocks_per_seg;
	return start_addr;
}
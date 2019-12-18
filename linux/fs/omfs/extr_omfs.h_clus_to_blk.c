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
struct omfs_sb_info {int s_block_shift; } ;
typedef  int sector_t ;

/* Variables and functions */

__attribute__((used)) static inline sector_t clus_to_blk(struct omfs_sb_info *sbi, sector_t block)
{
	return block << sbi->s_block_shift;
}
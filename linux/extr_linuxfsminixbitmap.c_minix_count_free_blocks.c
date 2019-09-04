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
typedef  scalar_t__ u32 ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct minix_sb_info {unsigned long s_log_zone_size; int /*<<< orphan*/  s_zmap; scalar_t__ s_firstdatazone; scalar_t__ s_nzones; } ;

/* Variables and functions */
 unsigned long count_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 

unsigned long minix_count_free_blocks(struct super_block *sb)
{
	struct minix_sb_info *sbi = minix_sb(sb);
	u32 bits = sbi->s_nzones - sbi->s_firstdatazone + 1;

	return (count_free(sbi->s_zmap, sb->s_blocksize, bits)
		<< sbi->s_log_zone_size);
}
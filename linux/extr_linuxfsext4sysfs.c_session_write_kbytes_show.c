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
struct super_block {TYPE_2__* s_bdev; } ;
struct ext4_sb_info {int s_sectors_written_start; TYPE_1__* s_buddy_cache; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  bd_part; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t STAT_WRITE ; 
 int part_stat_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t session_write_kbytes_show(struct ext4_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->s_buddy_cache->i_sb;

	if (!sb->s_bdev->bd_part)
		return snprintf(buf, PAGE_SIZE, "0\n");
	return snprintf(buf, PAGE_SIZE, "%lu\n",
			(part_stat_read(sb->s_bdev->bd_part,
					sectors[STAT_WRITE]) -
			 sbi->s_sectors_written_start) >> 1);
}
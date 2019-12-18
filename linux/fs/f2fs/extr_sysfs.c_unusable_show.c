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
struct f2fs_sb_info {scalar_t__ unusable_block_count; } ;
struct f2fs_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_CHECKPOINT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ f2fs_get_unusable_blocks (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t unusable_show(struct f2fs_attr *a,
		struct f2fs_sb_info *sbi, char *buf)
{
	block_t unusable;

	if (test_opt(sbi, DISABLE_CHECKPOINT))
		unusable = sbi->unusable_block_count;
	else
		unusable = f2fs_get_unusable_blocks(sbi);
	return snprintf(buf, PAGE_SIZE, "%llu\n",
		(unsigned long long)unusable);
}
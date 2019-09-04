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
struct f2fs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURSEG_HOT_NODE ; 
 int /*<<< orphan*/  write_normal_summaries (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void f2fs_write_node_summaries(struct f2fs_sb_info *sbi, block_t start_blk)
{
	write_normal_summaries(sbi, start_blk, CURSEG_HOT_NODE);
}
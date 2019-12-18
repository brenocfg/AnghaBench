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
struct super_block {int dummy; } ;
struct qnx6_sb_info {int s_blks_off; } ;
typedef  int /*<<< orphan*/  __fs32 ;

/* Variables and functions */
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned qnx6_get_devblock(struct super_block *sb, __fs32 block)
{
	struct qnx6_sb_info *sbi = QNX6_SB(sb);
	return fs32_to_cpu(sbi, block) + sbi->s_blks_off;
}
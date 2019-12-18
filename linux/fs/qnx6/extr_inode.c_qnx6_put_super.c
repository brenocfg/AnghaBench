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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct qnx6_sb_info {int /*<<< orphan*/  inodes; int /*<<< orphan*/  longfile; int /*<<< orphan*/  sb_buf; } ;

/* Variables and functions */
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qnx6_sb_info*) ; 

__attribute__((used)) static void qnx6_put_super(struct super_block *sb)
{
	struct qnx6_sb_info *qs = QNX6_SB(sb);
	brelse(qs->sb_buf);
	iput(qs->longfile);
	iput(qs->inodes);
	kfree(qs);
	sb->s_fs_info = NULL;
	return;
}
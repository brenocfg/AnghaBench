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
struct qnx4_sb_info {struct qnx4_sb_info* BitMap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qnx4_sb_info*) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 
 struct qnx4_sb_info* qnx4_sb (struct super_block*) ; 

__attribute__((used)) static void qnx4_kill_sb(struct super_block *sb)
{
	struct qnx4_sb_info *qs = qnx4_sb(sb);
	kill_block_super(sb);
	if (qs) {
		kfree(qs->BitMap);
		kfree(qs);
	}
}
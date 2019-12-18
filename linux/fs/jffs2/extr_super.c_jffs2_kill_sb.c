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
struct jffs2_sb_info {int dummy; } ;

/* Variables and functions */
 struct jffs2_sb_info* JFFS2_SB_INFO (struct super_block*) ; 
 int /*<<< orphan*/  jffs2_stop_garbage_collect_thread (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  kfree (struct jffs2_sb_info*) ; 
 int /*<<< orphan*/  kill_mtd_super (struct super_block*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static void jffs2_kill_sb(struct super_block *sb)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(sb);
	if (c && !sb_rdonly(sb))
		jffs2_stop_garbage_collect_thread(c);
	kill_mtd_super(sb);
	kfree(c);
}
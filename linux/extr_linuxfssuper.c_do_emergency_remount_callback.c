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
struct super_block {int s_flags; int /*<<< orphan*/  s_umount; scalar_t__ s_bdev; scalar_t__ s_root; } ;

/* Variables and functions */
 int SB_BORN ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  do_remount_sb (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_emergency_remount_callback(struct super_block *sb)
{
	down_write(&sb->s_umount);
	if (sb->s_root && sb->s_bdev && (sb->s_flags & SB_BORN) &&
	    !sb_rdonly(sb)) {
		/*
		 * What lock protects sb->s_flags??
		 */
		do_remount_sb(sb, SB_RDONLY, NULL, 1);
	}
	up_write(&sb->s_umount);
}
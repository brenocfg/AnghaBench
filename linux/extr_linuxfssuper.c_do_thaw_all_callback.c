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
struct super_block {int s_flags; int /*<<< orphan*/  s_umount; scalar_t__ s_root; } ;

/* Variables and functions */
 int SB_BORN ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emergency_thaw_bdev (struct super_block*) ; 
 int /*<<< orphan*/  thaw_super_locked (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_thaw_all_callback(struct super_block *sb)
{
	down_write(&sb->s_umount);
	if (sb->s_root && sb->s_flags & SB_BORN) {
		emergency_thaw_bdev(sb);
		thaw_super_locked(sb);
	} else {
		up_write(&sb->s_umount);
	}
}
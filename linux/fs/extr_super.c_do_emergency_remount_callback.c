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
struct super_block {int s_flags; int /*<<< orphan*/  s_umount; scalar_t__ s_root; scalar_t__ s_bdev; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct fs_context*) ; 
 int SB_BORN ; 
 int SB_FORCE ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct fs_context* fs_context_for_reconfigure (scalar_t__,int,int) ; 
 scalar_t__ parse_monolithic_mount_data (struct fs_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  reconfigure_super (struct fs_context*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_emergency_remount_callback(struct super_block *sb)
{
	down_write(&sb->s_umount);
	if (sb->s_root && sb->s_bdev && (sb->s_flags & SB_BORN) &&
	    !sb_rdonly(sb)) {
		struct fs_context *fc;

		fc = fs_context_for_reconfigure(sb->s_root,
					SB_RDONLY | SB_FORCE, SB_RDONLY);
		if (!IS_ERR(fc)) {
			if (parse_monolithic_mount_data(fc, NULL) == 0)
				(void)reconfigure_super(fc);
			put_fs_context(fc);
		}
	}
	up_write(&sb->s_umount);
}
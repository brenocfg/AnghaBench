#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_umount; struct ovl_fs* s_fs_info; } ;
struct ovl_fs {TYPE_1__* upper_mnt; } ;
struct TYPE_2__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int sync_filesystem (struct super_block*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_sync_fs(struct super_block *sb, int wait)
{
	struct ovl_fs *ofs = sb->s_fs_info;
	struct super_block *upper_sb;
	int ret;

	if (!ofs->upper_mnt)
		return 0;

	/*
	 * If this is a sync(2) call or an emergency sync, all the super blocks
	 * will be iterated, including upper_sb, so no need to do anything.
	 *
	 * If this is a syncfs(2) call, then we do need to call
	 * sync_filesystem() on upper_sb, but enough if we do it when being
	 * called with wait == 1.
	 */
	if (!wait)
		return 0;

	upper_sb = ofs->upper_mnt->mnt_sb;

	down_read(&upper_sb->s_umount);
	ret = sync_filesystem(upper_sb);
	up_read(&upper_sb->s_umount);

	return ret;
}
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
struct the_nilfs {int ns_mount_state; int /*<<< orphan*/  ns_sem; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_state; } ;

/* Variables and functions */
 int NILFS_ERROR_FS ; 
 int /*<<< orphan*/  NILFS_SB_COMMIT_ALL ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct nilfs_super_block**) ; 
 int /*<<< orphan*/  nilfs_commit_super (struct super_block*,int /*<<< orphan*/ ) ; 
 struct nilfs_super_block** nilfs_prepare_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_set_error(struct super_block *sb)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_super_block **sbp;

	down_write(&nilfs->ns_sem);
	if (!(nilfs->ns_mount_state & NILFS_ERROR_FS)) {
		nilfs->ns_mount_state |= NILFS_ERROR_FS;
		sbp = nilfs_prepare_super(sb, 0);
		if (likely(sbp)) {
			sbp[0]->s_state |= cpu_to_le16(NILFS_ERROR_FS);
			if (sbp[1])
				sbp[1]->s_state |= cpu_to_le16(NILFS_ERROR_FS);
			nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
		}
	}
	up_write(&nilfs->ns_sem);
}
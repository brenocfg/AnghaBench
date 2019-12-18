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
struct the_nilfs {int /*<<< orphan*/  ns_sem; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SB_COMMIT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct nilfs_super_block**) ; 
 int /*<<< orphan*/  nilfs_commit_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int nilfs_flush_device (struct the_nilfs*) ; 
 struct nilfs_super_block** nilfs_prepare_super (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_sb_dirty (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sb_will_flip (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_set_log_cursor (struct nilfs_super_block*,struct the_nilfs*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_sync_fs(struct super_block *sb, int wait)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_super_block **sbp;
	int err = 0;

	/* This function is called when super block should be written back */
	if (wait)
		err = nilfs_construct_segment(sb);

	down_write(&nilfs->ns_sem);
	if (nilfs_sb_dirty(nilfs)) {
		sbp = nilfs_prepare_super(sb, nilfs_sb_will_flip(nilfs));
		if (likely(sbp)) {
			nilfs_set_log_cursor(sbp[0], nilfs);
			nilfs_commit_super(sb, NILFS_SB_COMMIT);
		}
	}
	up_write(&nilfs->ns_sem);

	if (!err)
		err = nilfs_flush_device(nilfs);

	return err;
}
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
struct the_nilfs {int ns_mount_state; int /*<<< orphan*/  ns_sbsize; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {void* s_state; int /*<<< orphan*/  s_mtime; void* s_mnt_count; void* s_max_mnt_count; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int NILFS_DFL_MAX_MNT_COUNT ; 
 int NILFS_ERROR_FS ; 
 int /*<<< orphan*/  NILFS_SB_COMMIT_ALL ; 
 int NILFS_VALID_FS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (struct nilfs_super_block*,struct nilfs_super_block*,int /*<<< orphan*/ ) ; 
 int nilfs_commit_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 struct nilfs_super_block** nilfs_prepare_super (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_setup_super(struct super_block *sb, int is_mount)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_super_block **sbp;
	int max_mnt_count;
	int mnt_count;

	/* nilfs->ns_sem must be locked by the caller. */
	sbp = nilfs_prepare_super(sb, 0);
	if (!sbp)
		return -EIO;

	if (!is_mount)
		goto skip_mount_setup;

	max_mnt_count = le16_to_cpu(sbp[0]->s_max_mnt_count);
	mnt_count = le16_to_cpu(sbp[0]->s_mnt_count);

	if (nilfs->ns_mount_state & NILFS_ERROR_FS) {
		nilfs_msg(sb, KERN_WARNING, "mounting fs with errors");
#if 0
	} else if (max_mnt_count >= 0 && mnt_count >= max_mnt_count) {
		nilfs_msg(sb, KERN_WARNING, "maximal mount count reached");
#endif
	}
	if (!max_mnt_count)
		sbp[0]->s_max_mnt_count = cpu_to_le16(NILFS_DFL_MAX_MNT_COUNT);

	sbp[0]->s_mnt_count = cpu_to_le16(mnt_count + 1);
	sbp[0]->s_mtime = cpu_to_le64(ktime_get_real_seconds());

skip_mount_setup:
	sbp[0]->s_state =
		cpu_to_le16(le16_to_cpu(sbp[0]->s_state) & ~NILFS_VALID_FS);
	/* synchronize sbp[1] with sbp[0] */
	if (sbp[1])
		memcpy(sbp[1], sbp[0], nilfs->ns_sbsize);
	return nilfs_commit_super(sb, NILFS_SB_COMMIT_ALL);
}
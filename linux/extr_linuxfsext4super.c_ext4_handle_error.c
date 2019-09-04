#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_flags; } ;
struct TYPE_4__ {int j_flags; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_5__ {TYPE_1__* s_journal; int /*<<< orphan*/  s_mount_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 int /*<<< orphan*/  EXT4_MF_FS_ABORTED ; 
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 int JBD2_REC_ERR ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  WARN_ON_ERROR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jbd2_journal_abort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 scalar_t__ system_going_down () ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_handle_error(struct super_block *sb)
{
	if (test_opt(sb, WARN_ON_ERROR))
		WARN_ON_ONCE(1);

	if (sb_rdonly(sb))
		return;

	if (!test_opt(sb, ERRORS_CONT)) {
		journal_t *journal = EXT4_SB(sb)->s_journal;

		EXT4_SB(sb)->s_mount_flags |= EXT4_MF_FS_ABORTED;
		if (journal)
			jbd2_journal_abort(journal, -EIO);
	}
	/*
	 * We force ERRORS_RO behavior when system is rebooting. Otherwise we
	 * could panic during 'reboot -f' as the underlying device got already
	 * disabled.
	 */
	if (test_opt(sb, ERRORS_RO) || system_going_down()) {
		ext4_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
		/*
		 * Make sure updated value of ->s_mount_flags will be visible
		 * before ->s_flags update
		 */
		smp_wmb();
		sb->s_flags |= SB_RDONLY;
	} else if (test_opt(sb, ERRORS_PANIC)) {
		if (EXT4_SB(sb)->s_journal &&
		  !(EXT4_SB(sb)->s_journal->j_flags & JBD2_REC_ERR))
			return;
		panic("EXT4-fs (device %s): panic forced after error\n",
			sb->s_id);
	}
}
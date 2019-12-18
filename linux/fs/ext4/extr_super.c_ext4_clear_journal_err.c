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
struct super_block {int dummy; } ;
struct ext4_super_block {int /*<<< orphan*/  s_state; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_mount_state; int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXT4_ERROR_FS ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 
 char* ext4_decode_error (struct super_block*,int,char*) ; 
 int /*<<< orphan*/  ext4_has_feature_journal (struct super_block*) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  jbd2_journal_clear_err (int /*<<< orphan*/ *) ; 
 int jbd2_journal_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_update_sb_errno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_clear_journal_err(struct super_block *sb,
				   struct ext4_super_block *es)
{
	journal_t *journal;
	int j_errno;
	const char *errstr;

	BUG_ON(!ext4_has_feature_journal(sb));

	journal = EXT4_SB(sb)->s_journal;

	/*
	 * Now check for any error status which may have been recorded in the
	 * journal by a prior ext4_error() or ext4_abort()
	 */

	j_errno = jbd2_journal_errno(journal);
	if (j_errno) {
		char nbuf[16];

		errstr = ext4_decode_error(sb, j_errno, nbuf);
		ext4_warning(sb, "Filesystem error recorded "
			     "from previous mount: %s", errstr);
		ext4_warning(sb, "Marking fs in need of filesystem check.");

		EXT4_SB(sb)->s_mount_state |= EXT4_ERROR_FS;
		es->s_state |= cpu_to_le16(EXT4_ERROR_FS);
		ext4_commit_super(sb, 1);

		jbd2_journal_clear_err(journal);
		jbd2_journal_update_sb_errno(journal);
	}
}
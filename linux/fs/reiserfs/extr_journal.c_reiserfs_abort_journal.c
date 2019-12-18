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
struct super_block {int /*<<< orphan*/  s_flags; } ;
struct reiserfs_journal {int j_errno; int /*<<< orphan*/  j_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_ABORTED ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void reiserfs_abort_journal(struct super_block *sb, int errno)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	if (test_bit(J_ABORTED, &journal->j_state))
		return;

	if (!journal->j_errno)
		journal->j_errno = errno;

	sb->s_flags |= SB_RDONLY;
	set_bit(J_ABORTED, &journal->j_state);

#ifdef CONFIG_REISERFS_CHECK
	dump_stack();
#endif
}
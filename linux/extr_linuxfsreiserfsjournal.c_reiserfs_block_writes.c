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
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; int /*<<< orphan*/  t_super; } ;
struct reiserfs_journal {int j_must_wait; int /*<<< orphan*/  j_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  J_WRITERS_BLOCKED ; 
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void reiserfs_block_writes(struct reiserfs_transaction_handle *th)
{
	struct reiserfs_journal *journal = SB_JOURNAL(th->t_super);
	BUG_ON(!th->t_trans_id);
	journal->j_must_wait = 1;
	set_bit(J_WRITERS_BLOCKED, &journal->j_state);
	return;
}
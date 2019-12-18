#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/ * j_task; int /*<<< orphan*/  j_wait_done_commit; int /*<<< orphan*/  j_wait_commit; int /*<<< orphan*/  j_flags; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  JBD2_UNMOUNT ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void journal_kill_thread(journal_t *journal)
{
	write_lock(&journal->j_state_lock);
	journal->j_flags |= JBD2_UNMOUNT;

	while (journal->j_task) {
		write_unlock(&journal->j_state_lock);
		wake_up(&journal->j_wait_commit);
		wait_event(journal->j_wait_done_commit, journal->j_task == NULL);
		write_lock(&journal->j_state_lock);
	}
	write_unlock(&journal->j_state_lock);
}
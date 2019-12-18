#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_4__ {int /*<<< orphan*/  j_checkpoint_mutex; int /*<<< orphan*/  j_tail_sequence; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  __jbd2_update_log_tail (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void jbd2_update_log_tail(journal_t *journal, tid_t tid, unsigned long block)
{
	mutex_lock_io(&journal->j_checkpoint_mutex);
	if (tid_gt(tid, journal->j_tail_sequence))
		__jbd2_update_log_tail(journal, tid, block);
	mutex_unlock(&journal->j_checkpoint_mutex);
}
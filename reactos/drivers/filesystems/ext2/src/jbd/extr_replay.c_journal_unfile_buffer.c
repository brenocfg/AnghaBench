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
struct journal_head {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_list_lock; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  __journal_unfile_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  jbd_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_lock_bh_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jh2bh (struct journal_head*) ; 

void journal_unfile_buffer(journal_t *journal, struct journal_head *jh)
{
    jbd_lock_bh_state(jh2bh(jh));
    jbd_lock(&journal->j_list_lock);
    __journal_unfile_buffer(jh);
    jbd_unlock(&journal->j_list_lock);
    jbd_unlock_bh_state(jh2bh(jh));
}
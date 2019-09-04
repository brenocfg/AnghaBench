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
struct TYPE_3__ {struct journal_head* t_checkpoint_list; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {struct journal_head* b_cpprev; struct journal_head* b_cpnext; TYPE_1__* b_cp_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  J_ASSERT_JH (struct journal_head*,int) ; 
 scalar_t__ buffer_dirty (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_jbddirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd2_journal_grab_journal_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jh2bh (struct journal_head*) ; 

void __jbd2_journal_insert_checkpoint(struct journal_head *jh,
			       transaction_t *transaction)
{
	JBUFFER_TRACE(jh, "entry");
	J_ASSERT_JH(jh, buffer_dirty(jh2bh(jh)) || buffer_jbddirty(jh2bh(jh)));
	J_ASSERT_JH(jh, jh->b_cp_transaction == NULL);

	/* Get reference for checkpointing transaction */
	jbd2_journal_grab_journal_head(jh2bh(jh));
	jh->b_cp_transaction = transaction;

	if (!transaction->t_checkpoint_list) {
		jh->b_cpnext = jh->b_cpprev = jh;
	} else {
		jh->b_cpnext = transaction->t_checkpoint_list;
		jh->b_cpprev = transaction->t_checkpoint_list->b_cpprev;
		jh->b_cpprev->b_cpnext = jh;
		jh->b_cpnext->b_cpprev = jh;
	}
	transaction->t_checkpoint_list = jh;
}
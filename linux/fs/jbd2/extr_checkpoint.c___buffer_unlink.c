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
struct TYPE_2__ {struct journal_head* t_checkpoint_io_list; } ;
typedef  TYPE_1__ transaction_t ;
struct journal_head {struct journal_head* b_cpnext; TYPE_1__* b_cp_transaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  __buffer_unlink_first (struct journal_head*) ; 

__attribute__((used)) static inline void __buffer_unlink(struct journal_head *jh)
{
	transaction_t *transaction = jh->b_cp_transaction;

	__buffer_unlink_first(jh);
	if (transaction->t_checkpoint_io_list == jh) {
		transaction->t_checkpoint_io_list = jh->b_cpnext;
		if (transaction->t_checkpoint_io_list == jh)
			transaction->t_checkpoint_io_list = NULL;
	}
}
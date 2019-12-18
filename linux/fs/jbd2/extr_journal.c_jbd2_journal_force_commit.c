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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  J_ASSERT (int) ; 
 int __jbd2_journal_force_commit (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 

int jbd2_journal_force_commit(journal_t *journal)
{
	int ret;

	J_ASSERT(!current->journal_info);
	ret = __jbd2_journal_force_commit(journal);
	if (ret > 0)
		ret = 0;
	return ret;
}
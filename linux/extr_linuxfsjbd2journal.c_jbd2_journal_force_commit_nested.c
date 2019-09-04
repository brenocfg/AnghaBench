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
typedef  int /*<<< orphan*/  journal_t ;

/* Variables and functions */
 int __jbd2_journal_force_commit (int /*<<< orphan*/ *) ; 

int jbd2_journal_force_commit_nested(journal_t *journal)
{
	int ret;

	ret = __jbd2_journal_force_commit(journal);
	return ret > 0;
}
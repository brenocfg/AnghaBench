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

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  MemoryContextCheck (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextStats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  disable_statement_timeout () ; 
 int xact_started ; 

__attribute__((used)) static void
finish_xact_command(void)
{
	/* cancel active statement timeout after each command */
	disable_statement_timeout();

	if (xact_started)
	{
		CommitTransactionCommand();

#ifdef MEMORY_CONTEXT_CHECKING
		/* Check all memory contexts that weren't freed during commit */
		/* (those that were, were checked before being deleted) */
		MemoryContextCheck(TopMemoryContext);
#endif

#ifdef SHOW_MEMORY_STATS
		/* Print mem stats after each commit for leak tracking */
		MemoryContextStats(TopMemoryContext);
#endif

		xact_started = false;
	}
}
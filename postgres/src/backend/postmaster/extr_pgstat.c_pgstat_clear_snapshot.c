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
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * localBackendStatusTable ; 
 scalar_t__ localNumBackends ; 
 int /*<<< orphan*/ * pgStatDBHash ; 
 int /*<<< orphan*/ * pgStatLocalContext ; 

void
pgstat_clear_snapshot(void)
{
	/* Release memory, if any was allocated */
	if (pgStatLocalContext)
		MemoryContextDelete(pgStatLocalContext);

	/* Reset variables */
	pgStatLocalContext = NULL;
	pgStatDBHash = NULL;
	localBackendStatusTable = NULL;
	localNumBackends = 0;
}
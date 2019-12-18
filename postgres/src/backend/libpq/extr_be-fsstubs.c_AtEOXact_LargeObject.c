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
 int /*<<< orphan*/  close_lo_relation (int) ; 
 int /*<<< orphan*/ ** cookies ; 
 int cookies_size ; 
 int /*<<< orphan*/  deleteLOfd (int) ; 
 int /*<<< orphan*/ * fscxt ; 
 int /*<<< orphan*/  inv_close (int /*<<< orphan*/ *) ; 

void
AtEOXact_LargeObject(bool isCommit)
{
	int			i;

	if (fscxt == NULL)
		return;					/* no LO operations in this xact */

	/*
	 * Close LO fds and clear cookies array so that LO fds are no longer good.
	 * On abort we skip the close step.
	 */
	for (i = 0; i < cookies_size; i++)
	{
		if (cookies[i] != NULL)
		{
			if (isCommit)
				inv_close(cookies[i]);
			deleteLOfd(i);
		}
	}

	/* Needn't actually pfree since we're about to zap context */
	cookies = NULL;
	cookies_size = 0;

	/* Release the LO memory context to prevent permanent memory leaks. */
	MemoryContextDelete(fscxt);
	fscxt = NULL;

	/* Give inv_api.c a chance to clean up, too */
	close_lo_relation(isCommit);
}
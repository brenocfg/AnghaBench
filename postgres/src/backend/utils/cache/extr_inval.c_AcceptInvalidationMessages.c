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
 int /*<<< orphan*/  InvalidateSystemCaches () ; 
 int /*<<< orphan*/  LocalExecuteInvalidationMessage ; 
 int /*<<< orphan*/  ReceiveSharedInvalidMessages (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) ()) ; 

void
AcceptInvalidationMessages(void)
{
	ReceiveSharedInvalidMessages(LocalExecuteInvalidationMessage,
								 InvalidateSystemCaches);

	/*
	 * Test code to force cache flushes anytime a flush could happen.
	 *
	 * If used with CLOBBER_FREED_MEMORY, CLOBBER_CACHE_ALWAYS provides a
	 * fairly thorough test that the system contains no cache-flush hazards.
	 * However, it also makes the system unbelievably slow --- the regression
	 * tests take about 100 times longer than normal.
	 *
	 * If you're a glutton for punishment, try CLOBBER_CACHE_RECURSIVELY. This
	 * slows things by at least a factor of 10000, so I wouldn't suggest
	 * trying to run the entire regression tests that way.  It's useful to try
	 * a few simple tests, to make sure that cache reload isn't subject to
	 * internal cache-flush hazards, but after you've done a few thousand
	 * recursive reloads it's unlikely you'll learn more.
	 */
#if defined(CLOBBER_CACHE_ALWAYS)
	{
		static bool in_recursion = false;

		if (!in_recursion)
		{
			in_recursion = true;
			InvalidateSystemCaches();
			in_recursion = false;
		}
	}
#elif defined(CLOBBER_CACHE_RECURSIVELY)
	{
		static int	recursion_depth = 0;

		/* Maximum depth is arbitrary depending on your threshold of pain */
		if (recursion_depth < 3)
		{
			recursion_depth++;
			InvalidateSystemCaches();
			recursion_depth--;
		}
	}
#endif
}
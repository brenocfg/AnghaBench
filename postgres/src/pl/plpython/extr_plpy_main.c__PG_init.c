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
 int PY_MAJOR_VERSION ; 
 int /*<<< orphan*/  TEXTDOMAIN ; 
 scalar_t__ find_rendezvous_variable (char*) ; 
 int /*<<< orphan*/  pg_bindtextdomain (int /*<<< orphan*/ ) ; 
 int plpython_version_bitmask ; 
 int* plpython_version_bitmask_ptr ; 

void
_PG_init(void)
{
	int		  **bitmask_ptr;

	/*
	 * Set up a shared bitmask variable telling which Python version(s) are
	 * loaded into this process's address space.  If there's more than one, we
	 * cannot call into libpython for fear of causing crashes.  But postpone
	 * the actual failure for later, so that operations like pg_restore can
	 * load more than one plpython library so long as they don't try to do
	 * anything much with the language.
	 */
	bitmask_ptr = (int **) find_rendezvous_variable("plpython_version_bitmask");
	if (!(*bitmask_ptr))		/* am I the first? */
		*bitmask_ptr = &plpython_version_bitmask;
	/* Retain pointer to the agreed-on shared variable ... */
	plpython_version_bitmask_ptr = *bitmask_ptr;
	/* ... and announce my presence */
	*plpython_version_bitmask_ptr |= (1 << PY_MAJOR_VERSION);

	/*
	 * This should be safe even in the presence of conflicting plpythons, and
	 * it's necessary to do it before possibly throwing a conflict error, or
	 * the error message won't get localized.
	 */
	pg_bindtextdomain(TEXTDOMAIN);
}
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
struct statement {scalar_t__ oldlocale; int oldthreadlocale; } ;
typedef  scalar_t__ locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  _configthreadlocale (int) ; 
 int /*<<< orphan*/  free_statement (struct statement*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  uselocale (scalar_t__) ; 

void
ecpg_do_epilogue(struct statement *stmt)
{
	if (stmt == NULL)
		return;

#ifdef HAVE_USELOCALE
	if (stmt->oldlocale != (locale_t) 0)
		uselocale(stmt->oldlocale);
#else
	if (stmt->oldlocale)
		setlocale(LC_NUMERIC, stmt->oldlocale);
#ifdef HAVE__CONFIGTHREADLOCALE

	/*
	 * This is a bit trickier than it looks: if we failed partway through
	 * statement initialization, oldthreadlocale could still be 0.  But that's
	 * okay because a call with 0 is defined to be a no-op.
	 */
	if (stmt->oldthreadlocale != -1)
		(void) _configthreadlocale(stmt->oldthreadlocale);
#endif
#endif

	free_statement(stmt);
}
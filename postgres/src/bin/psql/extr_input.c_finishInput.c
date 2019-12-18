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
struct TYPE_2__ {int /*<<< orphan*/  histsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__ pset ; 
 int /*<<< orphan*/ * psql_history ; 
 int /*<<< orphan*/  saveHistory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ useHistory ; 

__attribute__((used)) static void
finishInput(void)
{
#ifdef USE_READLINE
	if (useHistory && psql_history)
	{
		(void) saveHistory(psql_history, pset.histsize);
		free(psql_history);
		psql_history = NULL;
	}
#endif
}
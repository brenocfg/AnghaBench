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
typedef  int /*<<< orphan*/  CachedPlanSource ;

/* Variables and functions */
 int /*<<< orphan*/  DropCachedPlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unnamed_stmt_psrc ; 

__attribute__((used)) static void
drop_unnamed_stmt(void)
{
	/* paranoia to avoid a dangling pointer in case of error */
	if (unnamed_stmt_psrc)
	{
		CachedPlanSource *psrc = unnamed_stmt_psrc;

		unnamed_stmt_psrc = NULL;
		DropCachedPlan(psrc);
	}
}
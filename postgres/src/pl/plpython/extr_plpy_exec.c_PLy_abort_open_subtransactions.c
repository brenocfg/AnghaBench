#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oldowner; int /*<<< orphan*/  oldcontext; } ;
typedef  TYPE_1__ PLySubtransactionData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ explicit_subtransactions ; 
 scalar_t__ linitial (scalar_t__) ; 
 scalar_t__ list_delete_first (scalar_t__) ; 
 int list_length (scalar_t__) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
PLy_abort_open_subtransactions(int save_subxact_level)
{
	Assert(save_subxact_level >= 0);

	while (list_length(explicit_subtransactions) > save_subxact_level)
	{
		PLySubtransactionData *subtransactiondata;

		Assert(explicit_subtransactions != NIL);

		ereport(WARNING,
				(errmsg("forcibly aborting a subtransaction that has not been exited")));

		RollbackAndReleaseCurrentSubTransaction();

		subtransactiondata = (PLySubtransactionData *) linitial(explicit_subtransactions);
		explicit_subtransactions = list_delete_first(explicit_subtransactions);

		MemoryContextSwitchTo(subtransactiondata->oldcontext);
		CurrentResourceOwner = subtransactiondata->oldowner;
		pfree(subtransactiondata);
	}
}
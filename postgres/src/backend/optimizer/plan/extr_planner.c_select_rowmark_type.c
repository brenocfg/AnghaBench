#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* GetForeignRowMarkType ) (TYPE_1__*,int) ;} ;
struct TYPE_6__ {scalar_t__ rtekind; scalar_t__ relkind; int /*<<< orphan*/  relid; } ;
typedef  int /*<<< orphan*/  RowMarkType ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  int LockClauseStrength ;
typedef  TYPE_2__ FdwRoutine ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 TYPE_2__* GetFdwRoutineByRelId (int /*<<< orphan*/ ) ; 
#define  LCS_FORKEYSHARE 132 
#define  LCS_FORNOKEYUPDATE 131 
#define  LCS_FORSHARE 130 
#define  LCS_FORUPDATE 129 
#define  LCS_NONE 128 
 scalar_t__ RELKIND_FOREIGN_TABLE ; 
 int /*<<< orphan*/  ROW_MARK_COPY ; 
 int /*<<< orphan*/  ROW_MARK_EXCLUSIVE ; 
 int /*<<< orphan*/  ROW_MARK_KEYSHARE ; 
 int /*<<< orphan*/  ROW_MARK_NOKEYEXCLUSIVE ; 
 int /*<<< orphan*/  ROW_MARK_REFERENCE ; 
 int /*<<< orphan*/  ROW_MARK_SHARE ; 
 scalar_t__ RTE_RELATION ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

RowMarkType
select_rowmark_type(RangeTblEntry *rte, LockClauseStrength strength)
{
	if (rte->rtekind != RTE_RELATION)
	{
		/* If it's not a table at all, use ROW_MARK_COPY */
		return ROW_MARK_COPY;
	}
	else if (rte->relkind == RELKIND_FOREIGN_TABLE)
	{
		/* Let the FDW select the rowmark type, if it wants to */
		FdwRoutine *fdwroutine = GetFdwRoutineByRelId(rte->relid);

		if (fdwroutine->GetForeignRowMarkType != NULL)
			return fdwroutine->GetForeignRowMarkType(rte, strength);
		/* Otherwise, use ROW_MARK_COPY by default */
		return ROW_MARK_COPY;
	}
	else
	{
		/* Regular table, apply the appropriate lock type */
		switch (strength)
		{
			case LCS_NONE:

				/*
				 * We don't need a tuple lock, only the ability to re-fetch
				 * the row.
				 */
				return ROW_MARK_REFERENCE;
				break;
			case LCS_FORKEYSHARE:
				return ROW_MARK_KEYSHARE;
				break;
			case LCS_FORSHARE:
				return ROW_MARK_SHARE;
				break;
			case LCS_FORNOKEYUPDATE:
				return ROW_MARK_NOKEYEXCLUSIVE;
				break;
			case LCS_FORUPDATE:
				return ROW_MARK_EXCLUSIVE;
				break;
		}
		elog(ERROR, "unrecognized LockClauseStrength %d", (int) strength);
		return ROW_MARK_EXCLUSIVE;	/* keep compiler quiet */
	}
}
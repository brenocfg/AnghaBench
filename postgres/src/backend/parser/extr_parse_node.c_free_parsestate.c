#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int p_next_resno; int /*<<< orphan*/ * p_target_relation; } ;
typedef  TYPE_1__ ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int MaxTupleAttributeNumber ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
free_parsestate(ParseState *pstate)
{
	/*
	 * Check that we did not produce too many resnos; at the very least we
	 * cannot allow more than 2^16, since that would exceed the range of a
	 * AttrNumber. It seems safest to use MaxTupleAttributeNumber.
	 */
	if (pstate->p_next_resno - 1 > MaxTupleAttributeNumber)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("target lists can have at most %d entries",
						MaxTupleAttributeNumber)));

	if (pstate->p_target_relation != NULL)
		table_close(pstate->p_target_relation, NoLock);

	pfree(pstate);
}
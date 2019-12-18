#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64 ;
struct TYPE_13__ {int n_members; TYPE_1__** members; int /*<<< orphan*/  ordered; } ;
struct TYPE_12__ {scalar_t__ amoplefttype; scalar_t__ amoprighttype; int amopstrategy; } ;
struct TYPE_11__ {scalar_t__ amproclefttype; scalar_t__ amprocrighttype; int amprocnum; } ;
struct TYPE_10__ {scalar_t__ lefttype; scalar_t__ righttype; int operatorset; int functionset; } ;
struct TYPE_9__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ OpFamilyOpFuncGroup ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_3__* Form_pg_amproc ;
typedef  TYPE_4__* Form_pg_amop ;
typedef  TYPE_5__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ palloc (int) ; 

List *
identify_opfamily_groups(CatCList *oprlist, CatCList *proclist)
{
	List	   *result = NIL;
	OpFamilyOpFuncGroup *thisgroup;
	Form_pg_amop oprform;
	Form_pg_amproc procform;
	int			io,
				ip;

	/* We need the lists to be ordered; should be true in normal operation */
	if (!oprlist->ordered || !proclist->ordered)
		elog(ERROR, "cannot validate operator family without ordered data");

	/*
	 * Advance through the lists concurrently.  Thanks to the ordering, we
	 * should see all operators and functions of a given datatype pair
	 * consecutively.
	 */
	thisgroup = NULL;
	io = ip = 0;
	if (io < oprlist->n_members)
	{
		oprform = (Form_pg_amop) GETSTRUCT(&oprlist->members[io]->tuple);
		io++;
	}
	else
		oprform = NULL;
	if (ip < proclist->n_members)
	{
		procform = (Form_pg_amproc) GETSTRUCT(&proclist->members[ip]->tuple);
		ip++;
	}
	else
		procform = NULL;

	while (oprform || procform)
	{
		if (oprform && thisgroup &&
			oprform->amoplefttype == thisgroup->lefttype &&
			oprform->amoprighttype == thisgroup->righttype)
		{
			/* Operator belongs to current group; include it and advance */

			/* Ignore strategy numbers outside supported range */
			if (oprform->amopstrategy > 0 && oprform->amopstrategy < 64)
				thisgroup->operatorset |= ((uint64) 1) << oprform->amopstrategy;

			if (io < oprlist->n_members)
			{
				oprform = (Form_pg_amop) GETSTRUCT(&oprlist->members[io]->tuple);
				io++;
			}
			else
				oprform = NULL;
			continue;
		}

		if (procform && thisgroup &&
			procform->amproclefttype == thisgroup->lefttype &&
			procform->amprocrighttype == thisgroup->righttype)
		{
			/* Procedure belongs to current group; include it and advance */

			/* Ignore function numbers outside supported range */
			if (procform->amprocnum > 0 && procform->amprocnum < 64)
				thisgroup->functionset |= ((uint64) 1) << procform->amprocnum;

			if (ip < proclist->n_members)
			{
				procform = (Form_pg_amproc) GETSTRUCT(&proclist->members[ip]->tuple);
				ip++;
			}
			else
				procform = NULL;
			continue;
		}

		/* Time for a new group */
		thisgroup = (OpFamilyOpFuncGroup *) palloc(sizeof(OpFamilyOpFuncGroup));
		if (oprform &&
			(!procform ||
			 (oprform->amoplefttype < procform->amproclefttype ||
			  (oprform->amoplefttype == procform->amproclefttype &&
			   oprform->amoprighttype < procform->amprocrighttype))))
		{
			thisgroup->lefttype = oprform->amoplefttype;
			thisgroup->righttype = oprform->amoprighttype;
		}
		else
		{
			thisgroup->lefttype = procform->amproclefttype;
			thisgroup->righttype = procform->amprocrighttype;
		}
		thisgroup->operatorset = thisgroup->functionset = 0;
		result = lappend(result, thisgroup);
	}

	return result;
}
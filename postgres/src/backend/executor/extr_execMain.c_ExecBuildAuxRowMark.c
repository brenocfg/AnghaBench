#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  resname ;
struct TYPE_6__ {void* toidAttNo; void* wholeAttNo; void* ctidAttNo; TYPE_1__* rowmark; } ;
struct TYPE_5__ {scalar_t__ markType; int rowmarkId; scalar_t__ rti; scalar_t__ prti; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ ExecRowMark ;
typedef  TYPE_2__ ExecAuxRowMark ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeNumberIsValid (void*) ; 
 int /*<<< orphan*/  ERROR ; 
 void* ExecFindJunkAttributeInTlist (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ROW_MARK_COPY ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

ExecAuxRowMark *
ExecBuildAuxRowMark(ExecRowMark *erm, List *targetlist)
{
	ExecAuxRowMark *aerm = (ExecAuxRowMark *) palloc0(sizeof(ExecAuxRowMark));
	char		resname[32];

	aerm->rowmark = erm;

	/* Look up the resjunk columns associated with this rowmark */
	if (erm->markType != ROW_MARK_COPY)
	{
		/* need ctid for all methods other than COPY */
		snprintf(resname, sizeof(resname), "ctid%u", erm->rowmarkId);
		aerm->ctidAttNo = ExecFindJunkAttributeInTlist(targetlist,
													   resname);
		if (!AttributeNumberIsValid(aerm->ctidAttNo))
			elog(ERROR, "could not find junk %s column", resname);
	}
	else
	{
		/* need wholerow if COPY */
		snprintf(resname, sizeof(resname), "wholerow%u", erm->rowmarkId);
		aerm->wholeAttNo = ExecFindJunkAttributeInTlist(targetlist,
														resname);
		if (!AttributeNumberIsValid(aerm->wholeAttNo))
			elog(ERROR, "could not find junk %s column", resname);
	}

	/* if child rel, need tableoid */
	if (erm->rti != erm->prti)
	{
		snprintf(resname, sizeof(resname), "tableoid%u", erm->rowmarkId);
		aerm->toidAttNo = ExecFindJunkAttributeInTlist(targetlist,
													   resname);
		if (!AttributeNumberIsValid(aerm->toidAttNo))
			elog(ERROR, "could not find junk %s column", resname);
	}

	return aerm;
}
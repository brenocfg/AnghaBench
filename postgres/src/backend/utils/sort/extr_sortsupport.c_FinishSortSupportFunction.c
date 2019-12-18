#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * comparator; } ;
typedef  TYPE_1__* SortSupport ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  BTORDER_PROC ; 
 int /*<<< orphan*/  BTSORTSUPPORT_PROC ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  PrepareSortSupportComparisonShim (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_proc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FinishSortSupportFunction(Oid opfamily, Oid opcintype, SortSupport ssup)
{
	Oid			sortSupportFunction;

	/* Look for a sort support function */
	sortSupportFunction = get_opfamily_proc(opfamily, opcintype, opcintype,
											BTSORTSUPPORT_PROC);
	if (OidIsValid(sortSupportFunction))
	{
		/*
		 * The sort support function can provide a comparator, but it can also
		 * choose not to so (e.g. based on the selected collation).
		 */
		OidFunctionCall1(sortSupportFunction, PointerGetDatum(ssup));
	}

	if (ssup->comparator == NULL)
	{
		Oid			sortFunction;

		sortFunction = get_opfamily_proc(opfamily, opcintype, opcintype,
										 BTORDER_PROC);

		if (!OidIsValid(sortFunction))
			elog(ERROR, "missing support function %d(%u,%u) in opfamily %u",
				 BTORDER_PROC, opcintype, opcintype, opfamily);

		/* We'll use a shim to call the old-style btree comparator */
		PrepareSortSupportComparisonShim(sortFunction, ssup);
	}
}
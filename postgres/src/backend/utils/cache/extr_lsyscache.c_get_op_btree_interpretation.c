#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int n_members; TYPE_1__** members; } ;
struct TYPE_10__ {scalar_t__ amopmethod; int /*<<< orphan*/  amoprighttype; int /*<<< orphan*/  amoplefttype; int /*<<< orphan*/  amopfamily; scalar_t__ amopstrategy; } ;
struct TYPE_9__ {int strategy; int /*<<< orphan*/  oprighttype; int /*<<< orphan*/  oplefttype; int /*<<< orphan*/  opfamily_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  tuple; } ;
typedef  int StrategyNumber ;
typedef  TYPE_2__ OpBtreeInterpretation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_3__* Form_pg_amop ;
typedef  TYPE_4__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 int /*<<< orphan*/  Assert (int) ; 
 int BTEqualStrategyNumber ; 
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int ROWCOMPARE_NE ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_4__*) ; 
 TYPE_4__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_negator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ palloc (int) ; 

List *
get_op_btree_interpretation(Oid opno)
{
	List	   *result = NIL;
	OpBtreeInterpretation *thisresult;
	CatCList   *catlist;
	int			i;

	/*
	 * Find all the pg_amop entries containing the operator.
	 */
	catlist = SearchSysCacheList1(AMOPOPID, ObjectIdGetDatum(opno));

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	op_tuple = &catlist->members[i]->tuple;
		Form_pg_amop op_form = (Form_pg_amop) GETSTRUCT(op_tuple);
		StrategyNumber op_strategy;

		/* must be btree */
		if (op_form->amopmethod != BTREE_AM_OID)
			continue;

		/* Get the operator's btree strategy number */
		op_strategy = (StrategyNumber) op_form->amopstrategy;
		Assert(op_strategy >= 1 && op_strategy <= 5);

		thisresult = (OpBtreeInterpretation *)
			palloc(sizeof(OpBtreeInterpretation));
		thisresult->opfamily_id = op_form->amopfamily;
		thisresult->strategy = op_strategy;
		thisresult->oplefttype = op_form->amoplefttype;
		thisresult->oprighttype = op_form->amoprighttype;
		result = lappend(result, thisresult);
	}

	ReleaseSysCacheList(catlist);

	/*
	 * If we didn't find any btree opfamily containing the operator, perhaps
	 * it is a <> operator.  See if it has a negator that is in an opfamily.
	 */
	if (result == NIL)
	{
		Oid			op_negator = get_negator(opno);

		if (OidIsValid(op_negator))
		{
			catlist = SearchSysCacheList1(AMOPOPID,
										  ObjectIdGetDatum(op_negator));

			for (i = 0; i < catlist->n_members; i++)
			{
				HeapTuple	op_tuple = &catlist->members[i]->tuple;
				Form_pg_amop op_form = (Form_pg_amop) GETSTRUCT(op_tuple);
				StrategyNumber op_strategy;

				/* must be btree */
				if (op_form->amopmethod != BTREE_AM_OID)
					continue;

				/* Get the operator's btree strategy number */
				op_strategy = (StrategyNumber) op_form->amopstrategy;
				Assert(op_strategy >= 1 && op_strategy <= 5);

				/* Only consider negators that are = */
				if (op_strategy != BTEqualStrategyNumber)
					continue;

				/* OK, report it with "strategy" ROWCOMPARE_NE */
				thisresult = (OpBtreeInterpretation *)
					palloc(sizeof(OpBtreeInterpretation));
				thisresult->opfamily_id = op_form->amopfamily;
				thisresult->strategy = ROWCOMPARE_NE;
				thisresult->oplefttype = op_form->amoplefttype;
				thisresult->oprighttype = op_form->amoprighttype;
				result = lappend(result, thisresult);
			}

			ReleaseSysCacheList(catlist);
		}
	}

	return result;
}
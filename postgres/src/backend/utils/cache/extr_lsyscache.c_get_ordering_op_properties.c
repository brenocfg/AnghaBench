#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16 ;
struct TYPE_8__ {int n_members; TYPE_1__** members; } ;
struct TYPE_7__ {scalar_t__ amopmethod; scalar_t__ amopstrategy; scalar_t__ amoplefttype; scalar_t__ amoprighttype; scalar_t__ amopfamily; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_amop ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 scalar_t__ BTGreaterStrategyNumber ; 
 scalar_t__ BTLessStrategyNumber ; 
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_3__*) ; 
 TYPE_3__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
get_ordering_op_properties(Oid opno,
						   Oid *opfamily, Oid *opcintype, int16 *strategy)
{
	bool		result = false;
	CatCList   *catlist;
	int			i;

	/* ensure outputs are initialized on failure */
	*opfamily = InvalidOid;
	*opcintype = InvalidOid;
	*strategy = 0;

	/*
	 * Search pg_amop to see if the target operator is registered as the "<"
	 * or ">" operator of any btree opfamily.
	 */
	catlist = SearchSysCacheList1(AMOPOPID, ObjectIdGetDatum(opno));

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	tuple = &catlist->members[i]->tuple;
		Form_pg_amop aform = (Form_pg_amop) GETSTRUCT(tuple);

		/* must be btree */
		if (aform->amopmethod != BTREE_AM_OID)
			continue;

		if (aform->amopstrategy == BTLessStrategyNumber ||
			aform->amopstrategy == BTGreaterStrategyNumber)
		{
			/* Found it ... should have consistent input types */
			if (aform->amoplefttype == aform->amoprighttype)
			{
				/* Found a suitable opfamily, return info */
				*opfamily = aform->amopfamily;
				*opcintype = aform->amoplefttype;
				*strategy = aform->amopstrategy;
				result = true;
				break;
			}
		}
	}

	ReleaseSysCacheList(catlist);

	return result;
}
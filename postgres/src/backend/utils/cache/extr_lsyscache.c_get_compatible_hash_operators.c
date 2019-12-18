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
struct TYPE_8__ {int n_members; TYPE_1__** members; } ;
struct TYPE_7__ {scalar_t__ amopmethod; scalar_t__ amopstrategy; scalar_t__ amoplefttype; scalar_t__ amoprighttype; int /*<<< orphan*/  amopfamily; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuple; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_amop ;
typedef  TYPE_3__ CatCList ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ *) ; 
 scalar_t__ HASH_AM_OID ; 
 scalar_t__ HTEqualStrategyNumber ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCacheList (TYPE_3__*) ; 
 TYPE_3__* SearchSysCacheList1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_member (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

bool
get_compatible_hash_operators(Oid opno,
							  Oid *lhs_opno, Oid *rhs_opno)
{
	bool		result = false;
	CatCList   *catlist;
	int			i;

	/* Ensure output args are initialized on failure */
	if (lhs_opno)
		*lhs_opno = InvalidOid;
	if (rhs_opno)
		*rhs_opno = InvalidOid;

	/*
	 * Search pg_amop to see if the target operator is registered as the "="
	 * operator of any hash opfamily.  If the operator is registered in
	 * multiple opfamilies, assume we can use any one.
	 */
	catlist = SearchSysCacheList1(AMOPOPID, ObjectIdGetDatum(opno));

	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	tuple = &catlist->members[i]->tuple;
		Form_pg_amop aform = (Form_pg_amop) GETSTRUCT(tuple);

		if (aform->amopmethod == HASH_AM_OID &&
			aform->amopstrategy == HTEqualStrategyNumber)
		{
			/* No extra lookup needed if given operator is single-type */
			if (aform->amoplefttype == aform->amoprighttype)
			{
				if (lhs_opno)
					*lhs_opno = opno;
				if (rhs_opno)
					*rhs_opno = opno;
				result = true;
				break;
			}

			/*
			 * Get the matching single-type operator(s).  Failure probably
			 * shouldn't happen --- it implies a bogus opfamily --- but
			 * continue looking if so.
			 */
			if (lhs_opno)
			{
				*lhs_opno = get_opfamily_member(aform->amopfamily,
												aform->amoplefttype,
												aform->amoplefttype,
												HTEqualStrategyNumber);
				if (!OidIsValid(*lhs_opno))
					continue;
				/* Matching LHS found, done if caller doesn't want RHS */
				if (!rhs_opno)
				{
					result = true;
					break;
				}
			}
			if (rhs_opno)
			{
				*rhs_opno = get_opfamily_member(aform->amopfamily,
												aform->amoprighttype,
												aform->amoprighttype,
												HTEqualStrategyNumber);
				if (!OidIsValid(*rhs_opno))
				{
					/* Forget any LHS operator from this opfamily */
					if (lhs_opno)
						*lhs_opno = InvalidOid;
					continue;
				}
				/* Matching RHS found, so done */
				result = true;
				break;
			}
		}
	}

	ReleaseSysCacheList(catlist);

	return result;
}
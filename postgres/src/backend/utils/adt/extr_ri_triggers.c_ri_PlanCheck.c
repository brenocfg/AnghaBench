#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  relowner; } ;
struct TYPE_5__ {scalar_t__ constr_queryno; } ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RI_QueryKey ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserIdAndSecContext (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ RI_PLAN_LAST_ON_PK ; 
 TYPE_4__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int SECURITY_LOCAL_USERID_CHANGE ; 
 int SECURITY_NOFORCE_RLS ; 
 int /*<<< orphan*/  SPI_keepplan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SPI_prepare (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_result_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetUserIdAndSecContext (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ri_HashPreparedPlan (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static SPIPlanPtr
ri_PlanCheck(const char *querystr, int nargs, Oid *argtypes,
			 RI_QueryKey *qkey, Relation fk_rel, Relation pk_rel)
{
	SPIPlanPtr	qplan;
	Relation	query_rel;
	Oid			save_userid;
	int			save_sec_context;

	/*
	 * Use the query type code to determine whether the query is run against
	 * the PK or FK table; we'll do the check as that table's owner
	 */
	if (qkey->constr_queryno <= RI_PLAN_LAST_ON_PK)
		query_rel = pk_rel;
	else
		query_rel = fk_rel;

	/* Switch to proper UID to perform check as */
	GetUserIdAndSecContext(&save_userid, &save_sec_context);
	SetUserIdAndSecContext(RelationGetForm(query_rel)->relowner,
						   save_sec_context | SECURITY_LOCAL_USERID_CHANGE |
						   SECURITY_NOFORCE_RLS);

	/* Create the plan */
	qplan = SPI_prepare(querystr, nargs, argtypes);

	if (qplan == NULL)
		elog(ERROR, "SPI_prepare returned %s for %s", SPI_result_code_string(SPI_result), querystr);

	/* Restore UID and security context */
	SetUserIdAndSecContext(save_userid, save_sec_context);

	/* Save the plan */
	SPI_keepplan(qplan);
	ri_HashPreparedPlan(qkey, qplan);

	return qplan;
}
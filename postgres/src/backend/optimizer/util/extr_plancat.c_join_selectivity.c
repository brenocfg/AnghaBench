#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  double float8 ;
typedef  int /*<<< orphan*/  SpecialJoinInfo ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  JoinType ;

/* Variables and functions */
 double DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Int16GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall5Coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,double) ; 
 int /*<<< orphan*/  get_oprjoin (int /*<<< orphan*/ ) ; 

Selectivity
join_selectivity(PlannerInfo *root,
				 Oid operatorid,
				 List *args,
				 Oid inputcollid,
				 JoinType jointype,
				 SpecialJoinInfo *sjinfo)
{
	RegProcedure oprjoin = get_oprjoin(operatorid);
	float8		result;

	/*
	 * if the oprjoin procedure is missing for whatever reason, use a
	 * selectivity of 0.5
	 */
	if (!oprjoin)
		return (Selectivity) 0.5;

	result = DatumGetFloat8(OidFunctionCall5Coll(oprjoin,
												 inputcollid,
												 PointerGetDatum(root),
												 ObjectIdGetDatum(operatorid),
												 PointerGetDatum(args),
												 Int16GetDatum(jointype),
												 PointerGetDatum(sjinfo)));

	if (result < 0.0 || result > 1.0)
		elog(ERROR, "invalid join selectivity: %f", result);

	return (Selectivity) result;
}
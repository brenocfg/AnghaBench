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
struct TYPE_8__ {int procost; int /*<<< orphan*/  prosupport; } ;
struct TYPE_7__ {int per_tuple; int /*<<< orphan*/  startup; } ;
struct TYPE_6__ {scalar_t__ per_tuple; scalar_t__ startup; int /*<<< orphan*/ * node; int /*<<< orphan*/  funcid; int /*<<< orphan*/ * root; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SupportRequestCost ;
typedef  TYPE_2__ QualCost ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_SupportRequestCost ; 
 int cpu_operator_cost ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
add_function_cost(PlannerInfo *root, Oid funcid, Node *node,
				  QualCost *cost)
{
	HeapTuple	proctup;
	Form_pg_proc procform;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for function %u", funcid);
	procform = (Form_pg_proc) GETSTRUCT(proctup);

	if (OidIsValid(procform->prosupport))
	{
		SupportRequestCost req;
		SupportRequestCost *sresult;

		req.type = T_SupportRequestCost;
		req.root = root;
		req.funcid = funcid;
		req.node = node;

		/* Initialize cost fields so that support function doesn't have to */
		req.startup = 0;
		req.per_tuple = 0;

		sresult = (SupportRequestCost *)
			DatumGetPointer(OidFunctionCall1(procform->prosupport,
											 PointerGetDatum(&req)));

		if (sresult == &req)
		{
			/* Success, so accumulate support function's estimate into *cost */
			cost->startup += req.startup;
			cost->per_tuple += req.per_tuple;
			ReleaseSysCache(proctup);
			return;
		}
	}

	/* No support function, or it failed, so rely on procost */
	cost->per_tuple += procform->procost * cpu_operator_cost;

	ReleaseSysCache(proctup);
}
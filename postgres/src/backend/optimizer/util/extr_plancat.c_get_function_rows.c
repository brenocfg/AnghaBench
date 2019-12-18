#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double prorows; int /*<<< orphan*/  prosupport; int /*<<< orphan*/  proretset; } ;
struct TYPE_4__ {double rows; int /*<<< orphan*/ * node; int /*<<< orphan*/  funcid; int /*<<< orphan*/ * root; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SupportRequestRows ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  T_SupportRequestRows ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

double
get_function_rows(PlannerInfo *root, Oid funcid, Node *node)
{
	HeapTuple	proctup;
	Form_pg_proc procform;
	double		result;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for function %u", funcid);
	procform = (Form_pg_proc) GETSTRUCT(proctup);

	Assert(procform->proretset);	/* else caller error */

	if (OidIsValid(procform->prosupport))
	{
		SupportRequestRows req;
		SupportRequestRows *sresult;

		req.type = T_SupportRequestRows;
		req.root = root;
		req.funcid = funcid;
		req.node = node;

		req.rows = 0;			/* just for sanity */

		sresult = (SupportRequestRows *)
			DatumGetPointer(OidFunctionCall1(procform->prosupport,
											 PointerGetDatum(&req)));

		if (sresult == &req)
		{
			/* Success */
			ReleaseSysCache(proctup);
			return req.rows;
		}
	}

	/* No support function, or it failed, so rely on prorows */
	result = procform->prorows;

	ReleaseSysCache(proctup);

	return result;
}
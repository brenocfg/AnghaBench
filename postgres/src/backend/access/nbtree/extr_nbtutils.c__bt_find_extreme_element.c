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
struct TYPE_8__ {TYPE_2__* indexRelation; } ;
struct TYPE_7__ {scalar_t__* rd_opcintype; int /*<<< orphan*/ * rd_opfamily; } ;
struct TYPE_6__ {scalar_t__ sk_subtype; int sk_attno; int /*<<< orphan*/  sk_collation; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  TYPE_1__* ScanKey ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  scalar_t__ Oid ;
typedef  TYPE_3__* IndexScanDesc ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FunctionCall2Coll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RegProcedureIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_opcode (scalar_t__) ; 
 scalar_t__ get_opfamily_member (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
_bt_find_extreme_element(IndexScanDesc scan, ScanKey skey,
						 StrategyNumber strat,
						 Datum *elems, int nelems)
{
	Relation	rel = scan->indexRelation;
	Oid			elemtype,
				cmp_op;
	RegProcedure cmp_proc;
	FmgrInfo	flinfo;
	Datum		result;
	int			i;

	/*
	 * Determine the nominal datatype of the array elements.  We have to
	 * support the convention that sk_subtype == InvalidOid means the opclass
	 * input type; this is a hack to simplify life for ScanKeyInit().
	 */
	elemtype = skey->sk_subtype;
	if (elemtype == InvalidOid)
		elemtype = rel->rd_opcintype[skey->sk_attno - 1];

	/*
	 * Look up the appropriate comparison operator in the opfamily.
	 *
	 * Note: it's possible that this would fail, if the opfamily is
	 * incomplete, but it seems quite unlikely that an opfamily would omit
	 * non-cross-type comparison operators for any datatype that it supports
	 * at all.
	 */
	cmp_op = get_opfamily_member(rel->rd_opfamily[skey->sk_attno - 1],
								 elemtype,
								 elemtype,
								 strat);
	if (!OidIsValid(cmp_op))
		elog(ERROR, "missing operator %d(%u,%u) in opfamily %u",
			 strat, elemtype, elemtype,
			 rel->rd_opfamily[skey->sk_attno - 1]);
	cmp_proc = get_opcode(cmp_op);
	if (!RegProcedureIsValid(cmp_proc))
		elog(ERROR, "missing oprcode for operator %u", cmp_op);

	fmgr_info(cmp_proc, &flinfo);

	Assert(nelems > 0);
	result = elems[0];
	for (i = 1; i < nelems; i++)
	{
		if (DatumGetBool(FunctionCall2Coll(&flinfo,
										   skey->sk_collation,
										   elems[i],
										   result)))
			result = elems[i];
	}

	return result;
}
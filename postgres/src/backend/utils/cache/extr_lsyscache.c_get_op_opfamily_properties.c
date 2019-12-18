#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int amopstrategy; int /*<<< orphan*/  amoprighttype; int /*<<< orphan*/  amoplefttype; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_amop ;

/* Variables and functions */
 int /*<<< orphan*/  AMOPOPID ; 
 int /*<<< orphan*/  AMOP_ORDER ; 
 int /*<<< orphan*/  AMOP_SEARCH ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
get_op_opfamily_properties(Oid opno, Oid opfamily, bool ordering_op,
						   int *strategy,
						   Oid *lefttype,
						   Oid *righttype)
{
	HeapTuple	tp;
	Form_pg_amop amop_tup;

	tp = SearchSysCache3(AMOPOPID,
						 ObjectIdGetDatum(opno),
						 CharGetDatum(ordering_op ? AMOP_ORDER : AMOP_SEARCH),
						 ObjectIdGetDatum(opfamily));
	if (!HeapTupleIsValid(tp))
		elog(ERROR, "operator %u is not a member of opfamily %u",
			 opno, opfamily);
	amop_tup = (Form_pg_amop) GETSTRUCT(tp);
	*strategy = amop_tup->amopstrategy;
	*lefttype = amop_tup->amoplefttype;
	*righttype = amop_tup->amoprighttype;
	ReleaseSysCache(tp);
}
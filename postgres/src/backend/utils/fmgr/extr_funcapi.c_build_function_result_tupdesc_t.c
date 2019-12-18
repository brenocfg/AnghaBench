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
typedef  int /*<<< orphan*/ * TupleDesc ;
struct TYPE_2__ {scalar_t__ prorettype; int /*<<< orphan*/  prokind; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_proc_proallargtypes ; 
 int /*<<< orphan*/  Anum_pg_proc_proargmodes ; 
 int /*<<< orphan*/  Anum_pg_proc_proargnames ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * build_function_result_tupdesc_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ heap_attisnull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

TupleDesc
build_function_result_tupdesc_t(HeapTuple procTuple)
{
	Form_pg_proc procform = (Form_pg_proc) GETSTRUCT(procTuple);
	Datum		proallargtypes;
	Datum		proargmodes;
	Datum		proargnames;
	bool		isnull;

	/* Return NULL if the function isn't declared to return RECORD */
	if (procform->prorettype != RECORDOID)
		return NULL;

	/* If there are no OUT parameters, return NULL */
	if (heap_attisnull(procTuple, Anum_pg_proc_proallargtypes, NULL) ||
		heap_attisnull(procTuple, Anum_pg_proc_proargmodes, NULL))
		return NULL;

	/* Get the data out of the tuple */
	proallargtypes = SysCacheGetAttr(PROCOID, procTuple,
									 Anum_pg_proc_proallargtypes,
									 &isnull);
	Assert(!isnull);
	proargmodes = SysCacheGetAttr(PROCOID, procTuple,
								  Anum_pg_proc_proargmodes,
								  &isnull);
	Assert(!isnull);
	proargnames = SysCacheGetAttr(PROCOID, procTuple,
								  Anum_pg_proc_proargnames,
								  &isnull);
	if (isnull)
		proargnames = PointerGetDatum(NULL);	/* just to be sure */

	return build_function_result_tupdesc_d(procform->prokind,
										   proallargtypes,
										   proargmodes,
										   proargnames);
}
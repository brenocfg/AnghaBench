#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * values; } ;
struct TYPE_4__ {int pronargs; TYPE_1__ proargtypes; int /*<<< orphan*/  proname; int /*<<< orphan*/  pronamespace; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be_qualified (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name_or_temp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

void
format_procedure_parts(Oid procedure_oid, List **objnames, List **objargs)
{
	HeapTuple	proctup;
	Form_pg_proc procform;
	int			nargs;
	int			i;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(procedure_oid));

	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for procedure with OID %u", procedure_oid);

	procform = (Form_pg_proc) GETSTRUCT(proctup);
	nargs = procform->pronargs;

	*objnames = list_make2(get_namespace_name_or_temp(procform->pronamespace),
						   pstrdup(NameStr(procform->proname)));
	*objargs = NIL;
	for (i = 0; i < nargs; i++)
	{
		Oid			thisargtype = procform->proargtypes.values[i];

		*objargs = lappend(*objargs, format_type_be_qualified(thisargtype));
	}

	ReleaseSysCache(proctup);
}
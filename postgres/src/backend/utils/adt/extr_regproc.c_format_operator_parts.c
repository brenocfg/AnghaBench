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
struct TYPE_2__ {scalar_t__ oprright; scalar_t__ oprleft; int /*<<< orphan*/  oprname; int /*<<< orphan*/  oprnamespace; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be_qualified (scalar_t__) ; 
 int /*<<< orphan*/  get_namespace_name_or_temp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

void
format_operator_parts(Oid operator_oid, List **objnames, List **objargs)
{
	HeapTuple	opertup;
	Form_pg_operator oprForm;

	opertup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operator_oid));
	if (!HeapTupleIsValid(opertup))
		elog(ERROR, "cache lookup failed for operator with OID %u",
			 operator_oid);

	oprForm = (Form_pg_operator) GETSTRUCT(opertup);
	*objnames = list_make2(get_namespace_name_or_temp(oprForm->oprnamespace),
						   pstrdup(NameStr(oprForm->oprname)));
	*objargs = NIL;
	if (oprForm->oprleft)
		*objargs = lappend(*objargs,
						   format_type_be_qualified(oprForm->oprleft));
	if (oprForm->oprright)
		*objargs = lappend(*objargs,
						   format_type_be_qualified(oprForm->oprright));

	ReleaseSysCache(opertup);
}
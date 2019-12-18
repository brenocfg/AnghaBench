#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ oprright; scalar_t__ oprleft; int /*<<< orphan*/  oprnamespace; int /*<<< orphan*/  oprname; } ;
struct TYPE_6__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  OperatorIsVisible (int) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 char* format_type_be (scalar_t__) ; 
 char* format_type_be_qualified (scalar_t__) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 char* quote_identifier (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *
format_operator_internal(Oid operator_oid, bool force_qualify)
{
	char	   *result;
	HeapTuple	opertup;

	opertup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operator_oid));

	if (HeapTupleIsValid(opertup))
	{
		Form_pg_operator operform = (Form_pg_operator) GETSTRUCT(opertup);
		char	   *oprname = NameStr(operform->oprname);
		char	   *nspname;
		StringInfoData buf;

		/* XXX no support here for bootstrap mode */
		Assert(!IsBootstrapProcessingMode());

		initStringInfo(&buf);

		/*
		 * Would this oper be found (given the right args) by regoperatorin?
		 * If not, or if caller explicitly requests it, we need to qualify it.
		 */
		if (force_qualify || !OperatorIsVisible(operator_oid))
		{
			nspname = get_namespace_name(operform->oprnamespace);
			appendStringInfo(&buf, "%s.",
							 quote_identifier(nspname));
		}

		appendStringInfo(&buf, "%s(", oprname);

		if (operform->oprleft)
			appendStringInfo(&buf, "%s,",
							 force_qualify ?
							 format_type_be_qualified(operform->oprleft) :
							 format_type_be(operform->oprleft));
		else
			appendStringInfoString(&buf, "NONE,");

		if (operform->oprright)
			appendStringInfo(&buf, "%s)",
							 force_qualify ?
							 format_type_be_qualified(operform->oprright) :
							 format_type_be(operform->oprright));
		else
			appendStringInfoString(&buf, "NONE)");

		result = buf.data;

		ReleaseSysCache(opertup);
	}
	else
	{
		/*
		 * If OID doesn't match any pg_operator entry, return it numerically
		 */
		result = (char *) palloc(NAMEDATALEN);
		snprintf(result, NAMEDATALEN, "%u", operator_oid);
	}

	return result;
}
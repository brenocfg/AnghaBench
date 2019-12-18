#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* values; } ;
struct TYPE_10__ {int pronargs; TYPE_1__ proargtypes; int /*<<< orphan*/  pronamespace; int /*<<< orphan*/  proname; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  int Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ FunctionIsVisible (int) ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_2__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int) ; 
 int /*<<< orphan*/  format_type_be_qualified (int) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quote_qualified_identifier (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *
format_procedure_internal(Oid procedure_oid, bool force_qualify)
{
	char	   *result;
	HeapTuple	proctup;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(procedure_oid));

	if (HeapTupleIsValid(proctup))
	{
		Form_pg_proc procform = (Form_pg_proc) GETSTRUCT(proctup);
		char	   *proname = NameStr(procform->proname);
		int			nargs = procform->pronargs;
		int			i;
		char	   *nspname;
		StringInfoData buf;

		/* XXX no support here for bootstrap mode */
		Assert(!IsBootstrapProcessingMode());

		initStringInfo(&buf);

		/*
		 * Would this proc be found (given the right args) by regprocedurein?
		 * If not, or if caller requests it, we need to qualify it.
		 */
		if (!force_qualify && FunctionIsVisible(procedure_oid))
			nspname = NULL;
		else
			nspname = get_namespace_name(procform->pronamespace);

		appendStringInfo(&buf, "%s(",
						 quote_qualified_identifier(nspname, proname));
		for (i = 0; i < nargs; i++)
		{
			Oid			thisargtype = procform->proargtypes.values[i];

			if (i > 0)
				appendStringInfoChar(&buf, ',');
			appendStringInfoString(&buf,
								   force_qualify ?
								   format_type_be_qualified(thisargtype) :
								   format_type_be(thisargtype));
		}
		appendStringInfoChar(&buf, ')');

		result = buf.data;

		ReleaseSysCache(proctup);
	}
	else
	{
		/* If OID doesn't match any pg_proc entry, return it numerically */
		result = (char *) palloc(NAMEDATALEN);
		snprintf(result, NAMEDATALEN, "%u", procedure_oid);
	}

	return result;
}
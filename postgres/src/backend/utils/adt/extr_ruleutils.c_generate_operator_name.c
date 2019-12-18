#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int oprkind; int /*<<< orphan*/  oprnamespace; int /*<<< orphan*/  oprname; } ;
struct TYPE_7__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  int /*<<< orphan*/ * Operator ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_operator ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEROID ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoChar (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/ * left_oper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 int /*<<< orphan*/ * oper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ oprid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quote_identifier (char*) ; 
 int /*<<< orphan*/ * right_oper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static char *
generate_operator_name(Oid operid, Oid arg1, Oid arg2)
{
	StringInfoData buf;
	HeapTuple	opertup;
	Form_pg_operator operform;
	char	   *oprname;
	char	   *nspname;
	Operator	p_result;

	initStringInfo(&buf);

	opertup = SearchSysCache1(OPEROID, ObjectIdGetDatum(operid));
	if (!HeapTupleIsValid(opertup))
		elog(ERROR, "cache lookup failed for operator %u", operid);
	operform = (Form_pg_operator) GETSTRUCT(opertup);
	oprname = NameStr(operform->oprname);

	/*
	 * The idea here is to schema-qualify only if the parser would fail to
	 * resolve the correct operator given the unqualified op name with the
	 * specified argtypes.
	 */
	switch (operform->oprkind)
	{
		case 'b':
			p_result = oper(NULL, list_make1(makeString(oprname)), arg1, arg2,
							true, -1);
			break;
		case 'l':
			p_result = left_oper(NULL, list_make1(makeString(oprname)), arg2,
								 true, -1);
			break;
		case 'r':
			p_result = right_oper(NULL, list_make1(makeString(oprname)), arg1,
								  true, -1);
			break;
		default:
			elog(ERROR, "unrecognized oprkind: %d", operform->oprkind);
			p_result = NULL;	/* keep compiler quiet */
			break;
	}

	if (p_result != NULL && oprid(p_result) == operid)
		nspname = NULL;
	else
	{
		nspname = get_namespace_name(operform->oprnamespace);
		appendStringInfo(&buf, "OPERATOR(%s.", quote_identifier(nspname));
	}

	appendStringInfoString(&buf, oprname);

	if (nspname)
		appendStringInfoChar(&buf, ')');

	if (p_result != NULL)
		ReleaseSysCache(p_result);

	ReleaseSysCache(opertup);

	return buf.data;
}
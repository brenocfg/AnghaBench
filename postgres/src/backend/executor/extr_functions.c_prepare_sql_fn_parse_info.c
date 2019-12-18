#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  values; } ;
struct TYPE_7__ {int pronargs; TYPE_1__ proargtypes; int /*<<< orphan*/  proname; } ;
struct TYPE_6__ {int nargs; scalar_t__* argtypes; int /*<<< orphan*/ * argnames; scalar_t__ collation; int /*<<< orphan*/  fname; } ;
typedef  TYPE_2__* SQLFunctionParseInfoPtr ;
typedef  int /*<<< orphan*/  SQLFunctionParseInfo ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_proc ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_proc_proargmodes ; 
 int /*<<< orphan*/  Anum_pg_proc_proargnames ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsPolymorphicType (scalar_t__) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCNAMEARGSNSP ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (scalar_t__) ; 
 scalar_t__ get_call_expr_argtype (int /*<<< orphan*/ *,int) ; 
 int get_func_input_arg_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

SQLFunctionParseInfoPtr
prepare_sql_fn_parse_info(HeapTuple procedureTuple,
						  Node *call_expr,
						  Oid inputCollation)
{
	SQLFunctionParseInfoPtr pinfo;
	Form_pg_proc procedureStruct = (Form_pg_proc) GETSTRUCT(procedureTuple);
	int			nargs;

	pinfo = (SQLFunctionParseInfoPtr) palloc0(sizeof(SQLFunctionParseInfo));

	/* Function's name (only) can be used to qualify argument names */
	pinfo->fname = pstrdup(NameStr(procedureStruct->proname));

	/* Save the function's input collation */
	pinfo->collation = inputCollation;

	/*
	 * Copy input argument types from the pg_proc entry, then resolve any
	 * polymorphic types.
	 */
	pinfo->nargs = nargs = procedureStruct->pronargs;
	if (nargs > 0)
	{
		Oid		   *argOidVect;
		int			argnum;

		argOidVect = (Oid *) palloc(nargs * sizeof(Oid));
		memcpy(argOidVect,
			   procedureStruct->proargtypes.values,
			   nargs * sizeof(Oid));

		for (argnum = 0; argnum < nargs; argnum++)
		{
			Oid			argtype = argOidVect[argnum];

			if (IsPolymorphicType(argtype))
			{
				argtype = get_call_expr_argtype(call_expr, argnum);
				if (argtype == InvalidOid)
					ereport(ERROR,
							(errcode(ERRCODE_DATATYPE_MISMATCH),
							 errmsg("could not determine actual type of argument declared %s",
									format_type_be(argOidVect[argnum]))));
				argOidVect[argnum] = argtype;
			}
		}

		pinfo->argtypes = argOidVect;
	}

	/*
	 * Collect names of arguments, too, if any
	 */
	if (nargs > 0)
	{
		Datum		proargnames;
		Datum		proargmodes;
		int			n_arg_names;
		bool		isNull;

		proargnames = SysCacheGetAttr(PROCNAMEARGSNSP, procedureTuple,
									  Anum_pg_proc_proargnames,
									  &isNull);
		if (isNull)
			proargnames = PointerGetDatum(NULL);	/* just to be sure */

		proargmodes = SysCacheGetAttr(PROCNAMEARGSNSP, procedureTuple,
									  Anum_pg_proc_proargmodes,
									  &isNull);
		if (isNull)
			proargmodes = PointerGetDatum(NULL);	/* just to be sure */

		n_arg_names = get_func_input_arg_names(proargnames, proargmodes,
											   &pinfo->argnames);

		/* Paranoia: ignore the result if too few array entries */
		if (n_arg_names < nargs)
			pinfo->argnames = NULL;
	}
	else
		pinfo->argnames = NULL;

	return pinfo;
}
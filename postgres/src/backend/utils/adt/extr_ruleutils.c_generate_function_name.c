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
struct TYPE_2__ {int /*<<< orphan*/  pronamespace; int /*<<< orphan*/  provariadic; int /*<<< orphan*/  proname; } ;
typedef  scalar_t__ ParseExprKind ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ FuncDetailCode ;
typedef  TYPE_1__* Form_pg_proc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EXPR_KIND_GROUP_BY ; 
 scalar_t__ FUNCDETAIL_AGGREGATE ; 
 scalar_t__ FUNCDETAIL_NORMAL ; 
 scalar_t__ FUNCDETAIL_NOTFOUND ; 
 scalar_t__ FUNCDETAIL_WINDOWFUNC ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ func_get_detail (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int,int,scalar_t__*,scalar_t__*,int*,int*,scalar_t__*,scalar_t__**,int /*<<< orphan*/ *) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 char* quote_qualified_identifier (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static char *
generate_function_name(Oid funcid, int nargs, List *argnames, Oid *argtypes,
					   bool has_variadic, bool *use_variadic_p,
					   ParseExprKind special_exprkind)
{
	char	   *result;
	HeapTuple	proctup;
	Form_pg_proc procform;
	char	   *proname;
	bool		use_variadic;
	char	   *nspname;
	FuncDetailCode p_result;
	Oid			p_funcid;
	Oid			p_rettype;
	bool		p_retset;
	int			p_nvargs;
	Oid			p_vatype;
	Oid		   *p_true_typeids;
	bool		force_qualify = false;

	proctup = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(proctup))
		elog(ERROR, "cache lookup failed for function %u", funcid);
	procform = (Form_pg_proc) GETSTRUCT(proctup);
	proname = NameStr(procform->proname);

	/*
	 * Due to parser hacks to avoid needing to reserve CUBE, we need to force
	 * qualification in some special cases.
	 */
	if (special_exprkind == EXPR_KIND_GROUP_BY)
	{
		if (strcmp(proname, "cube") == 0 || strcmp(proname, "rollup") == 0)
			force_qualify = true;
	}

	/*
	 * Determine whether VARIADIC should be printed.  We must do this first
	 * since it affects the lookup rules in func_get_detail().
	 *
	 * We always print VARIADIC if the function has a merged variadic-array
	 * argument.  Note that this is always the case for functions taking a
	 * VARIADIC argument type other than VARIADIC ANY.  If we omitted VARIADIC
	 * and printed the array elements as separate arguments, the call could
	 * match a newer non-VARIADIC function.
	 */
	if (use_variadic_p)
	{
		/* Parser should not have set funcvariadic unless fn is variadic */
		Assert(!has_variadic || OidIsValid(procform->provariadic));
		use_variadic = has_variadic;
		*use_variadic_p = use_variadic;
	}
	else
	{
		Assert(!has_variadic);
		use_variadic = false;
	}

	/*
	 * The idea here is to schema-qualify only if the parser would fail to
	 * resolve the correct function given the unqualified func name with the
	 * specified argtypes and VARIADIC flag.  But if we already decided to
	 * force qualification, then we can skip the lookup and pretend we didn't
	 * find it.
	 */
	if (!force_qualify)
		p_result = func_get_detail(list_make1(makeString(proname)),
								   NIL, argnames, nargs, argtypes,
								   !use_variadic, true,
								   &p_funcid, &p_rettype,
								   &p_retset, &p_nvargs, &p_vatype,
								   &p_true_typeids, NULL);
	else
	{
		p_result = FUNCDETAIL_NOTFOUND;
		p_funcid = InvalidOid;
	}

	if ((p_result == FUNCDETAIL_NORMAL ||
		 p_result == FUNCDETAIL_AGGREGATE ||
		 p_result == FUNCDETAIL_WINDOWFUNC) &&
		p_funcid == funcid)
		nspname = NULL;
	else
		nspname = get_namespace_name(procform->pronamespace);

	result = quote_qualified_identifier(nspname, proname);

	ReleaseSysCache(proctup);

	return result;
}
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
struct TYPE_10__ {int /*<<< orphan*/  location; int /*<<< orphan*/  fields; } ;
struct TYPE_9__ {int /*<<< orphan*/  p_last_srf; int /*<<< orphan*/  p_ref_hook_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__* SQLFunctionParseInfoPtr ;
typedef  TYPE_2__ ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_3__ ColumnRef ;

/* Variables and functions */
 int /*<<< orphan*/  A_Star ; 
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 scalar_t__ IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ParseFuncOrColumn (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  String ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * llast (int /*<<< orphan*/ ) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ ) ; 
 scalar_t__ lthird (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sql_fn_resolve_param_name (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 char* strVal (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
sql_fn_post_column_ref(ParseState *pstate, ColumnRef *cref, Node *var)
{
	SQLFunctionParseInfoPtr pinfo = (SQLFunctionParseInfoPtr) pstate->p_ref_hook_state;
	int			nnames;
	Node	   *field1;
	Node	   *subfield = NULL;
	const char *name1;
	const char *name2 = NULL;
	Node	   *param;

	/*
	 * Never override a table-column reference.  This corresponds to
	 * considering the parameter names to appear in a scope outside the
	 * individual SQL commands, which is what we want.
	 */
	if (var != NULL)
		return NULL;

	/*----------
	 * The allowed syntaxes are:
	 *
	 * A		A = parameter name
	 * A.B		A = function name, B = parameter name
	 *			OR: A = record-typed parameter name, B = field name
	 *			(the first possibility takes precedence)
	 * A.B.C	A = function name, B = record-typed parameter name,
	 *			C = field name
	 * A.*		Whole-row reference to composite parameter A.
	 * A.B.*	Same, with A = function name, B = parameter name
	 *
	 * Here, it's sufficient to ignore the "*" in the last two cases --- the
	 * main parser will take care of expanding the whole-row reference.
	 *----------
	 */
	nnames = list_length(cref->fields);

	if (nnames > 3)
		return NULL;

	if (IsA(llast(cref->fields), A_Star))
		nnames--;

	field1 = (Node *) linitial(cref->fields);
	Assert(IsA(field1, String));
	name1 = strVal(field1);
	if (nnames > 1)
	{
		subfield = (Node *) lsecond(cref->fields);
		Assert(IsA(subfield, String));
		name2 = strVal(subfield);
	}

	if (nnames == 3)
	{
		/*
		 * Three-part name: if the first part doesn't match the function name,
		 * we can fail immediately. Otherwise, look up the second part, and
		 * take the third part to be a field reference.
		 */
		if (strcmp(name1, pinfo->fname) != 0)
			return NULL;

		param = sql_fn_resolve_param_name(pinfo, name2, cref->location);

		subfield = (Node *) lthird(cref->fields);
		Assert(IsA(subfield, String));
	}
	else if (nnames == 2 && strcmp(name1, pinfo->fname) == 0)
	{
		/*
		 * Two-part name with first part matching function name: first see if
		 * second part matches any parameter name.
		 */
		param = sql_fn_resolve_param_name(pinfo, name2, cref->location);

		if (param)
		{
			/* Yes, so this is a parameter reference, no subfield */
			subfield = NULL;
		}
		else
		{
			/* No, so try to match as parameter name and subfield */
			param = sql_fn_resolve_param_name(pinfo, name1, cref->location);
		}
	}
	else
	{
		/* Single name, or parameter name followed by subfield */
		param = sql_fn_resolve_param_name(pinfo, name1, cref->location);
	}

	if (!param)
		return NULL;			/* No match */

	if (subfield)
	{
		/*
		 * Must be a reference to a field of a composite parameter; otherwise
		 * ParseFuncOrColumn will return NULL, and we'll fail back at the
		 * caller.
		 */
		param = ParseFuncOrColumn(pstate,
								  list_make1(subfield),
								  list_make1(param),
								  pstate->p_last_srf,
								  NULL,
								  false,
								  cref->location);
	}

	return param;
}
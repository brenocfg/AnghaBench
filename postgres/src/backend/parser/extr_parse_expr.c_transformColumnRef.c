#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  location; int /*<<< orphan*/  fields; } ;
struct TYPE_17__ {int p_expr_kind; int /*<<< orphan*/ * (* p_post_columnref_hook ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  p_last_srf; int /*<<< orphan*/ * (* p_pre_columnref_hook ) (TYPE_1__*,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ ColumnRef ;

/* Variables and functions */
 int /*<<< orphan*/  A_Star ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_AMBIGUOUS_COLUMN ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
#define  EXPR_KIND_ALTER_COL_TRANSFORM 168 
#define  EXPR_KIND_CALL_ARGUMENT 167 
#define  EXPR_KIND_CHECK_CONSTRAINT 166 
#define  EXPR_KIND_COLUMN_DEFAULT 165 
#define  EXPR_KIND_COPY_WHERE 164 
#define  EXPR_KIND_DISTINCT_ON 163 
#define  EXPR_KIND_DOMAIN_CHECK 162 
#define  EXPR_KIND_EXECUTE_PARAMETER 161 
#define  EXPR_KIND_FILTER 160 
#define  EXPR_KIND_FROM_FUNCTION 159 
#define  EXPR_KIND_FROM_SUBSELECT 158 
#define  EXPR_KIND_FUNCTION_DEFAULT 157 
#define  EXPR_KIND_GENERATED_COLUMN 156 
#define  EXPR_KIND_GROUP_BY 155 
#define  EXPR_KIND_HAVING 154 
#define  EXPR_KIND_INDEX_EXPRESSION 153 
#define  EXPR_KIND_INDEX_PREDICATE 152 
#define  EXPR_KIND_INSERT_TARGET 151 
#define  EXPR_KIND_JOIN_ON 150 
#define  EXPR_KIND_JOIN_USING 149 
#define  EXPR_KIND_LIMIT 148 
#define  EXPR_KIND_NONE 147 
#define  EXPR_KIND_OFFSET 146 
#define  EXPR_KIND_ORDER_BY 145 
#define  EXPR_KIND_OTHER 144 
#define  EXPR_KIND_PARTITION_BOUND 143 
#define  EXPR_KIND_PARTITION_EXPRESSION 142 
#define  EXPR_KIND_POLICY 141 
#define  EXPR_KIND_RETURNING 140 
#define  EXPR_KIND_SELECT_TARGET 139 
#define  EXPR_KIND_TRIGGER_WHEN 138 
#define  EXPR_KIND_UPDATE_SOURCE 137 
#define  EXPR_KIND_UPDATE_TARGET 136 
#define  EXPR_KIND_VALUES 135 
#define  EXPR_KIND_VALUES_SINGLE 134 
#define  EXPR_KIND_WHERE 133 
#define  EXPR_KIND_WINDOW_FRAME_GROUPS 132 
#define  EXPR_KIND_WINDOW_FRAME_RANGE 131 
#define  EXPR_KIND_WINDOW_FRAME_ROWS 130 
#define  EXPR_KIND_WINDOW_ORDER 129 
#define  EXPR_KIND_WINDOW_PARTITION 128 
 int IsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ParseFuncOrColumn (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  String ; 
 char* _ (char*) ; 
 int /*<<< orphan*/ * colNameToVar (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,char const*) ; 
 int /*<<< orphan*/  errorMissingColumn (TYPE_1__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errorMissingRTE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 scalar_t__ lfourth (int /*<<< orphan*/ ) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ *) ; 
 scalar_t__ lsecond (int /*<<< orphan*/ ) ; 
 scalar_t__ lthird (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeRangeVar (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeString (char*) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * refnameRangeTblEntry (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * scanRTEForColumn (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* strVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transformWholeRowRef (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *
transformColumnRef(ParseState *pstate, ColumnRef *cref)
{
	Node	   *node = NULL;
	char	   *nspname = NULL;
	char	   *relname = NULL;
	char	   *colname = NULL;
	RangeTblEntry *rte;
	int			levels_up;
	enum
	{
		CRERR_NO_COLUMN,
		CRERR_NO_RTE,
		CRERR_WRONG_DB,
		CRERR_TOO_MANY
	}			crerr = CRERR_NO_COLUMN;
	const char *err;

	/*
	 * Check to see if the column reference is in an invalid place within the
	 * query.  We allow column references in most places, except in default
	 * expressions and partition bound expressions.
	 */
	err = NULL;
	switch (pstate->p_expr_kind)
	{
		case EXPR_KIND_NONE:
			Assert(false);		/* can't happen */
			break;
		case EXPR_KIND_OTHER:
		case EXPR_KIND_JOIN_ON:
		case EXPR_KIND_JOIN_USING:
		case EXPR_KIND_FROM_SUBSELECT:
		case EXPR_KIND_FROM_FUNCTION:
		case EXPR_KIND_WHERE:
		case EXPR_KIND_POLICY:
		case EXPR_KIND_HAVING:
		case EXPR_KIND_FILTER:
		case EXPR_KIND_WINDOW_PARTITION:
		case EXPR_KIND_WINDOW_ORDER:
		case EXPR_KIND_WINDOW_FRAME_RANGE:
		case EXPR_KIND_WINDOW_FRAME_ROWS:
		case EXPR_KIND_WINDOW_FRAME_GROUPS:
		case EXPR_KIND_SELECT_TARGET:
		case EXPR_KIND_INSERT_TARGET:
		case EXPR_KIND_UPDATE_SOURCE:
		case EXPR_KIND_UPDATE_TARGET:
		case EXPR_KIND_GROUP_BY:
		case EXPR_KIND_ORDER_BY:
		case EXPR_KIND_DISTINCT_ON:
		case EXPR_KIND_LIMIT:
		case EXPR_KIND_OFFSET:
		case EXPR_KIND_RETURNING:
		case EXPR_KIND_VALUES:
		case EXPR_KIND_VALUES_SINGLE:
		case EXPR_KIND_CHECK_CONSTRAINT:
		case EXPR_KIND_DOMAIN_CHECK:
		case EXPR_KIND_FUNCTION_DEFAULT:
		case EXPR_KIND_INDEX_EXPRESSION:
		case EXPR_KIND_INDEX_PREDICATE:
		case EXPR_KIND_ALTER_COL_TRANSFORM:
		case EXPR_KIND_EXECUTE_PARAMETER:
		case EXPR_KIND_TRIGGER_WHEN:
		case EXPR_KIND_PARTITION_EXPRESSION:
		case EXPR_KIND_CALL_ARGUMENT:
		case EXPR_KIND_COPY_WHERE:
		case EXPR_KIND_GENERATED_COLUMN:
			/* okay */
			break;

		case EXPR_KIND_COLUMN_DEFAULT:
			err = _("cannot use column reference in DEFAULT expression");
			break;
		case EXPR_KIND_PARTITION_BOUND:
			err = _("cannot use column reference in partition bound expression");
			break;

			/*
			 * There is intentionally no default: case here, so that the
			 * compiler will warn if we add a new ParseExprKind without
			 * extending this switch.  If we do see an unrecognized value at
			 * runtime, the behavior will be the same as for EXPR_KIND_OTHER,
			 * which is sane anyway.
			 */
	}
	if (err)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg_internal("%s", err),
				 parser_errposition(pstate, cref->location)));

	/*
	 * Give the PreParseColumnRefHook, if any, first shot.  If it returns
	 * non-null then that's all, folks.
	 */
	if (pstate->p_pre_columnref_hook != NULL)
	{
		node = pstate->p_pre_columnref_hook(pstate, cref);
		if (node != NULL)
			return node;
	}

	/*----------
	 * The allowed syntaxes are:
	 *
	 * A		First try to resolve as unqualified column name;
	 *			if no luck, try to resolve as unqualified table name (A.*).
	 * A.B		A is an unqualified table name; B is either a
	 *			column or function name (trying column name first).
	 * A.B.C	schema A, table B, col or func name C.
	 * A.B.C.D	catalog A, schema B, table C, col or func D.
	 * A.*		A is an unqualified table name; means whole-row value.
	 * A.B.*	whole-row value of table B in schema A.
	 * A.B.C.*	whole-row value of table C in schema B in catalog A.
	 *
	 * We do not need to cope with bare "*"; that will only be accepted by
	 * the grammar at the top level of a SELECT list, and transformTargetList
	 * will take care of it before it ever gets here.  Also, "A.*" etc will
	 * be expanded by transformTargetList if they appear at SELECT top level,
	 * so here we are only going to see them as function or operator inputs.
	 *
	 * Currently, if a catalog name is given then it must equal the current
	 * database name; we check it here and then discard it.
	 *----------
	 */
	switch (list_length(cref->fields))
	{
		case 1:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);

				Assert(IsA(field1, String));
				colname = strVal(field1);

				/* Try to identify as an unqualified column */
				node = colNameToVar(pstate, colname, false, cref->location);

				if (node == NULL)
				{
					/*
					 * Not known as a column of any range-table entry.
					 *
					 * Try to find the name as a relation.  Note that only
					 * relations already entered into the rangetable will be
					 * recognized.
					 *
					 * This is a hack for backwards compatibility with
					 * PostQUEL-inspired syntax.  The preferred form now is
					 * "rel.*".
					 */
					rte = refnameRangeTblEntry(pstate, NULL, colname,
											   cref->location,
											   &levels_up);
					if (rte)
						node = transformWholeRowRef(pstate, rte,
													cref->location);
				}
				break;
			}
		case 2:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);
				Node	   *field2 = (Node *) lsecond(cref->fields);

				Assert(IsA(field1, String));
				relname = strVal(field1);

				/* Locate the referenced RTE */
				rte = refnameRangeTblEntry(pstate, nspname, relname,
										   cref->location,
										   &levels_up);
				if (rte == NULL)
				{
					crerr = CRERR_NO_RTE;
					break;
				}

				/* Whole-row reference? */
				if (IsA(field2, A_Star))
				{
					node = transformWholeRowRef(pstate, rte, cref->location);
					break;
				}

				Assert(IsA(field2, String));
				colname = strVal(field2);

				/* Try to identify as a column of the RTE */
				node = scanRTEForColumn(pstate, rte, colname, cref->location,
										0, NULL);
				if (node == NULL)
				{
					/* Try it as a function call on the whole row */
					node = transformWholeRowRef(pstate, rte, cref->location);
					node = ParseFuncOrColumn(pstate,
											 list_make1(makeString(colname)),
											 list_make1(node),
											 pstate->p_last_srf,
											 NULL,
											 false,
											 cref->location);
				}
				break;
			}
		case 3:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);
				Node	   *field2 = (Node *) lsecond(cref->fields);
				Node	   *field3 = (Node *) lthird(cref->fields);

				Assert(IsA(field1, String));
				nspname = strVal(field1);
				Assert(IsA(field2, String));
				relname = strVal(field2);

				/* Locate the referenced RTE */
				rte = refnameRangeTblEntry(pstate, nspname, relname,
										   cref->location,
										   &levels_up);
				if (rte == NULL)
				{
					crerr = CRERR_NO_RTE;
					break;
				}

				/* Whole-row reference? */
				if (IsA(field3, A_Star))
				{
					node = transformWholeRowRef(pstate, rte, cref->location);
					break;
				}

				Assert(IsA(field3, String));
				colname = strVal(field3);

				/* Try to identify as a column of the RTE */
				node = scanRTEForColumn(pstate, rte, colname, cref->location,
										0, NULL);
				if (node == NULL)
				{
					/* Try it as a function call on the whole row */
					node = transformWholeRowRef(pstate, rte, cref->location);
					node = ParseFuncOrColumn(pstate,
											 list_make1(makeString(colname)),
											 list_make1(node),
											 pstate->p_last_srf,
											 NULL,
											 false,
											 cref->location);
				}
				break;
			}
		case 4:
			{
				Node	   *field1 = (Node *) linitial(cref->fields);
				Node	   *field2 = (Node *) lsecond(cref->fields);
				Node	   *field3 = (Node *) lthird(cref->fields);
				Node	   *field4 = (Node *) lfourth(cref->fields);
				char	   *catname;

				Assert(IsA(field1, String));
				catname = strVal(field1);
				Assert(IsA(field2, String));
				nspname = strVal(field2);
				Assert(IsA(field3, String));
				relname = strVal(field3);

				/*
				 * We check the catalog name and then ignore it.
				 */
				if (strcmp(catname, get_database_name(MyDatabaseId)) != 0)
				{
					crerr = CRERR_WRONG_DB;
					break;
				}

				/* Locate the referenced RTE */
				rte = refnameRangeTblEntry(pstate, nspname, relname,
										   cref->location,
										   &levels_up);
				if (rte == NULL)
				{
					crerr = CRERR_NO_RTE;
					break;
				}

				/* Whole-row reference? */
				if (IsA(field4, A_Star))
				{
					node = transformWholeRowRef(pstate, rte, cref->location);
					break;
				}

				Assert(IsA(field4, String));
				colname = strVal(field4);

				/* Try to identify as a column of the RTE */
				node = scanRTEForColumn(pstate, rte, colname, cref->location,
										0, NULL);
				if (node == NULL)
				{
					/* Try it as a function call on the whole row */
					node = transformWholeRowRef(pstate, rte, cref->location);
					node = ParseFuncOrColumn(pstate,
											 list_make1(makeString(colname)),
											 list_make1(node),
											 pstate->p_last_srf,
											 NULL,
											 false,
											 cref->location);
				}
				break;
			}
		default:
			crerr = CRERR_TOO_MANY; /* too many dotted names */
			break;
	}

	/*
	 * Now give the PostParseColumnRefHook, if any, a chance.  We pass the
	 * translation-so-far so that it can throw an error if it wishes in the
	 * case that it has a conflicting interpretation of the ColumnRef. (If it
	 * just translates anyway, we'll throw an error, because we can't undo
	 * whatever effects the preceding steps may have had on the pstate.) If it
	 * returns NULL, use the standard translation, or throw a suitable error
	 * if there is none.
	 */
	if (pstate->p_post_columnref_hook != NULL)
	{
		Node	   *hookresult;

		hookresult = pstate->p_post_columnref_hook(pstate, cref, node);
		if (node == NULL)
			node = hookresult;
		else if (hookresult != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_AMBIGUOUS_COLUMN),
					 errmsg("column reference \"%s\" is ambiguous",
							NameListToString(cref->fields)),
					 parser_errposition(pstate, cref->location)));
	}

	/*
	 * Throw error if no translation found.
	 */
	if (node == NULL)
	{
		switch (crerr)
		{
			case CRERR_NO_COLUMN:
				errorMissingColumn(pstate, relname, colname, cref->location);
				break;
			case CRERR_NO_RTE:
				errorMissingRTE(pstate, makeRangeVar(nspname, relname,
													 cref->location));
				break;
			case CRERR_WRONG_DB:
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("cross-database references are not implemented: %s",
								NameListToString(cref->fields)),
						 parser_errposition(pstate, cref->location)));
				break;
			case CRERR_TOO_MANY:
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("improper qualified name (too many dotted names): %s",
								NameListToString(cref->fields)),
						 parser_errposition(pstate, cref->location)));
				break;
		}
	}

	return node;
}
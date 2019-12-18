#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  location; int /*<<< orphan*/ * fields; } ;
struct TYPE_15__ {int /*<<< orphan*/ * (* p_post_columnref_hook ) (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* p_pre_columnref_hook ) (TYPE_1__*,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ ParseState ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ ColumnRef ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_AMBIGUOUS_COLUMN ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * ExpandAllTables (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ExpandRowReference (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ExpandSingleTable (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errorMissingRTE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsecond (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lthird (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeRangeVar (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * refnameRangeTblEntry (TYPE_1__*,char*,char*,int /*<<< orphan*/ ,int*) ; 
 char* strVal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
ExpandColumnRefStar(ParseState *pstate, ColumnRef *cref,
					bool make_target_entry)
{
	List	   *fields = cref->fields;
	int			numnames = list_length(fields);

	if (numnames == 1)
	{
		/*
		 * Target item is a bare '*', expand all tables
		 *
		 * (e.g., SELECT * FROM emp, dept)
		 *
		 * Since the grammar only accepts bare '*' at top level of SELECT, we
		 * need not handle the make_target_entry==false case here.
		 */
		Assert(make_target_entry);
		return ExpandAllTables(pstate, cref->location);
	}
	else
	{
		/*
		 * Target item is relation.*, expand that table
		 *
		 * (e.g., SELECT emp.*, dname FROM emp, dept)
		 *
		 * Note: this code is a lot like transformColumnRef; it's tempting to
		 * call that instead and then replace the resulting whole-row Var with
		 * a list of Vars.  However, that would leave us with the RTE's
		 * selectedCols bitmap showing the whole row as needing select
		 * permission, as well as the individual columns.  That would be
		 * incorrect (since columns added later shouldn't need select
		 * permissions).  We could try to remove the whole-row permission bit
		 * after the fact, but duplicating code is less messy.
		 */
		char	   *nspname = NULL;
		char	   *relname = NULL;
		RangeTblEntry *rte = NULL;
		int			levels_up;
		enum
		{
			CRSERR_NO_RTE,
			CRSERR_WRONG_DB,
			CRSERR_TOO_MANY
		}			crserr = CRSERR_NO_RTE;

		/*
		 * Give the PreParseColumnRefHook, if any, first shot.  If it returns
		 * non-null then we should use that expression.
		 */
		if (pstate->p_pre_columnref_hook != NULL)
		{
			Node	   *node;

			node = pstate->p_pre_columnref_hook(pstate, cref);
			if (node != NULL)
				return ExpandRowReference(pstate, node, make_target_entry);
		}

		switch (numnames)
		{
			case 2:
				relname = strVal(linitial(fields));
				rte = refnameRangeTblEntry(pstate, nspname, relname,
										   cref->location,
										   &levels_up);
				break;
			case 3:
				nspname = strVal(linitial(fields));
				relname = strVal(lsecond(fields));
				rte = refnameRangeTblEntry(pstate, nspname, relname,
										   cref->location,
										   &levels_up);
				break;
			case 4:
				{
					char	   *catname = strVal(linitial(fields));

					/*
					 * We check the catalog name and then ignore it.
					 */
					if (strcmp(catname, get_database_name(MyDatabaseId)) != 0)
					{
						crserr = CRSERR_WRONG_DB;
						break;
					}
					nspname = strVal(lsecond(fields));
					relname = strVal(lthird(fields));
					rte = refnameRangeTblEntry(pstate, nspname, relname,
											   cref->location,
											   &levels_up);
					break;
				}
			default:
				crserr = CRSERR_TOO_MANY;
				break;
		}

		/*
		 * Now give the PostParseColumnRefHook, if any, a chance. We cheat a
		 * bit by passing the RangeTblEntry, not a Var, as the planned
		 * translation.  (A single Var wouldn't be strictly correct anyway.
		 * This convention allows hooks that really care to know what is
		 * happening.)
		 */
		if (pstate->p_post_columnref_hook != NULL)
		{
			Node	   *node;

			node = pstate->p_post_columnref_hook(pstate, cref,
												 (Node *) rte);
			if (node != NULL)
			{
				if (rte != NULL)
					ereport(ERROR,
							(errcode(ERRCODE_AMBIGUOUS_COLUMN),
							 errmsg("column reference \"%s\" is ambiguous",
									NameListToString(cref->fields)),
							 parser_errposition(pstate, cref->location)));
				return ExpandRowReference(pstate, node, make_target_entry);
			}
		}

		/*
		 * Throw error if no translation found.
		 */
		if (rte == NULL)
		{
			switch (crserr)
			{
				case CRSERR_NO_RTE:
					errorMissingRTE(pstate, makeRangeVar(nspname, relname,
														 cref->location));
					break;
				case CRSERR_WRONG_DB:
					ereport(ERROR,
							(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
							 errmsg("cross-database references are not implemented: %s",
									NameListToString(cref->fields)),
							 parser_errposition(pstate, cref->location)));
					break;
				case CRSERR_TOO_MANY:
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("improper qualified name (too many dotted names): %s",
									NameListToString(cref->fields)),
							 parser_errposition(pstate, cref->location)));
					break;
			}
		}

		/*
		 * OK, expand the RTE into fields.
		 */
		return ExpandSingleTable(pstate, rte, cref->location, make_target_entry);
	}
}
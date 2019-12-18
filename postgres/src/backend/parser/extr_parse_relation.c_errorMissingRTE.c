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
struct TYPE_10__ {TYPE_1__* eref; scalar_t__ alias; } ;
struct TYPE_9__ {int /*<<< orphan*/  location; int /*<<< orphan*/  relname; } ;
struct TYPE_8__ {char* aliasname; } ;
typedef  TYPE_2__ RangeVar ;
typedef  TYPE_3__ RangeTblEntry ;
typedef  int /*<<< orphan*/  ParseState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_UNDEFINED_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,char const*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser_errposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* refnameRangeTblEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 TYPE_3__* searchRangeTableForRel (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
errorMissingRTE(ParseState *pstate, RangeVar *relation)
{
	RangeTblEntry *rte;
	int			sublevels_up;
	const char *badAlias = NULL;

	/*
	 * Check to see if there are any potential matches in the query's
	 * rangetable.  (Note: cases involving a bad schema name in the RangeVar
	 * will throw error immediately here.  That seems OK.)
	 */
	rte = searchRangeTableForRel(pstate, relation);

	/*
	 * If we found a match that has an alias and the alias is visible in the
	 * namespace, then the problem is probably use of the relation's real name
	 * instead of its alias, ie "SELECT foo.* FROM foo f". This mistake is
	 * common enough to justify a specific hint.
	 *
	 * If we found a match that doesn't meet those criteria, assume the
	 * problem is illegal use of a relation outside its scope, as in the
	 * MySQL-ism "SELECT ... FROM a, b LEFT JOIN c ON (a.x = c.y)".
	 */
	if (rte && rte->alias &&
		strcmp(rte->eref->aliasname, relation->relname) != 0 &&
		refnameRangeTblEntry(pstate, NULL, rte->eref->aliasname,
							 relation->location,
							 &sublevels_up) == rte)
		badAlias = rte->eref->aliasname;

	if (rte)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("invalid reference to FROM-clause entry for table \"%s\"",
						relation->relname),
				 (badAlias ?
				  errhint("Perhaps you meant to reference the table alias \"%s\".",
						  badAlias) :
				  errhint("There is an entry for table \"%s\", but it cannot be referenced from this part of the query.",
						  rte->eref->aliasname)),
				 parser_errposition(pstate, relation->location)));
	else
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_TABLE),
				 errmsg("missing FROM-clause entry for table \"%s\"",
						relation->relname),
				 parser_errposition(pstate, relation->location)));
}
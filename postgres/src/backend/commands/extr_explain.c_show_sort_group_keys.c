#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ expr; } ;
typedef  TYPE_1__ TargetEntry ;
struct TYPE_18__ {scalar_t__ verbose; int /*<<< orphan*/  rtable; int /*<<< orphan*/  deparse_cxt; } ;
struct TYPE_17__ {int /*<<< orphan*/  targetlist; } ;
struct TYPE_16__ {TYPE_4__* plan; } ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ StringInfoData ;
typedef  TYPE_3__ PlanState ;
typedef  TYPE_4__ Plan ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_5__ ExplainState ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExplainPropertyList (char const*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_2__*,char*) ; 
 char* deparse_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_tle_by_resno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/ * set_deparse_context_planstate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_sortorder_options (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
show_sort_group_keys(PlanState *planstate, const char *qlabel,
					 int nkeys, AttrNumber *keycols,
					 Oid *sortOperators, Oid *collations, bool *nullsFirst,
					 List *ancestors, ExplainState *es)
{
	Plan	   *plan = planstate->plan;
	List	   *context;
	List	   *result = NIL;
	StringInfoData sortkeybuf;
	bool		useprefix;
	int			keyno;

	if (nkeys <= 0)
		return;

	initStringInfo(&sortkeybuf);

	/* Set up deparsing context */
	context = set_deparse_context_planstate(es->deparse_cxt,
											(Node *) planstate,
											ancestors);
	useprefix = (list_length(es->rtable) > 1 || es->verbose);

	for (keyno = 0; keyno < nkeys; keyno++)
	{
		/* find key expression in tlist */
		AttrNumber	keyresno = keycols[keyno];
		TargetEntry *target = get_tle_by_resno(plan->targetlist,
											   keyresno);
		char	   *exprstr;

		if (!target)
			elog(ERROR, "no tlist entry for key %d", keyresno);
		/* Deparse the expression, showing any top-level cast */
		exprstr = deparse_expression((Node *) target->expr, context,
									 useprefix, true);
		resetStringInfo(&sortkeybuf);
		appendStringInfoString(&sortkeybuf, exprstr);
		/* Append sort order information, if relevant */
		if (sortOperators != NULL)
			show_sortorder_options(&sortkeybuf,
								   (Node *) target->expr,
								   sortOperators[keyno],
								   collations[keyno],
								   nullsFirst[keyno]);
		/* Emit one property-list item per sort key */
		result = lappend(result, pstrdup(sortkeybuf.data));
	}

	ExplainPropertyList(qlabel, result, es);
}
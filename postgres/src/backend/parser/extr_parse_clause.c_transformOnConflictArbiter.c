#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ conname; scalar_t__ whereClause; scalar_t__ indexElems; } ;
struct TYPE_15__ {scalar_t__ action; TYPE_4__* infer; } ;
struct TYPE_14__ {TYPE_1__* p_target_rangetblentry; int /*<<< orphan*/  p_target_relation; int /*<<< orphan*/ * p_namespace; } ;
struct TYPE_13__ {int /*<<< orphan*/  selectedCols; int /*<<< orphan*/  requiredPerms; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ ParseState ;
typedef  TYPE_3__ OnConflictClause ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_4__ InferClause ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_SELECT ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPR_KIND_INDEX_PREDICATE ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ IsCatalogRelation (int /*<<< orphan*/ ) ; 
 void* NIL ; 
 scalar_t__ ONCONFLICT_UPDATE ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationIsUsedAsCatalogTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addRTEtoQuery (TYPE_2__*,TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  bms_add_members (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  exprLocation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_relation_constraint_attnos (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_errposition (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * resolve_unique_index_expr (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transformExpr (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

void
transformOnConflictArbiter(ParseState *pstate,
						   OnConflictClause *onConflictClause,
						   List **arbiterExpr, Node **arbiterWhere,
						   Oid *constraint)
{
	InferClause *infer = onConflictClause->infer;

	*arbiterExpr = NIL;
	*arbiterWhere = NULL;
	*constraint = InvalidOid;

	if (onConflictClause->action == ONCONFLICT_UPDATE && !infer)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("ON CONFLICT DO UPDATE requires inference specification or constraint name"),
				 errhint("For example, ON CONFLICT (column_name)."),
				 parser_errposition(pstate,
									exprLocation((Node *) onConflictClause))));

	/*
	 * To simplify certain aspects of its design, speculative insertion into
	 * system catalogs is disallowed
	 */
	if (IsCatalogRelation(pstate->p_target_relation))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("ON CONFLICT is not supported with system catalog tables"),
				 parser_errposition(pstate,
									exprLocation((Node *) onConflictClause))));

	/* Same applies to table used by logical decoding as catalog table */
	if (RelationIsUsedAsCatalogTable(pstate->p_target_relation))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("ON CONFLICT is not supported on table \"%s\" used as a catalog table",
						RelationGetRelationName(pstate->p_target_relation)),
				 parser_errposition(pstate,
									exprLocation((Node *) onConflictClause))));

	/* ON CONFLICT DO NOTHING does not require an inference clause */
	if (infer)
	{
		List	   *save_namespace;

		/*
		 * While we process the arbiter expressions, accept only non-qualified
		 * references to the target table. Hide any other relations.
		 */
		save_namespace = pstate->p_namespace;
		pstate->p_namespace = NIL;
		addRTEtoQuery(pstate, pstate->p_target_rangetblentry,
					  false, false, true);

		if (infer->indexElems)
			*arbiterExpr = resolve_unique_index_expr(pstate, infer,
													 pstate->p_target_relation);

		/*
		 * Handling inference WHERE clause (for partial unique index
		 * inference)
		 */
		if (infer->whereClause)
			*arbiterWhere = transformExpr(pstate, infer->whereClause,
										  EXPR_KIND_INDEX_PREDICATE);

		pstate->p_namespace = save_namespace;

		/*
		 * If the arbiter is specified by constraint name, get the constraint
		 * OID and mark the constrained columns as requiring SELECT privilege,
		 * in the same way as would have happened if the arbiter had been
		 * specified by explicit reference to the constraint's index columns.
		 */
		if (infer->conname)
		{
			Oid			relid = RelationGetRelid(pstate->p_target_relation);
			RangeTblEntry *rte = pstate->p_target_rangetblentry;
			Bitmapset  *conattnos;

			conattnos = get_relation_constraint_attnos(relid, infer->conname,
													   false, constraint);

			/* Make sure the rel as a whole is marked for SELECT access */
			rte->requiredPerms |= ACL_SELECT;
			/* Mark the constrained columns as requiring SELECT access */
			rte->selectedCols = bms_add_members(rte->selectedCols, conattnos);
		}
	}

	/*
	 * It's convenient to form a list of expressions based on the
	 * representation used by CREATE INDEX, since the same restrictions are
	 * appropriate (e.g. on subqueries).  However, from here on, a dedicated
	 * primnode representation is used for inference elements, and so
	 * assign_query_collations() can be trusted to do the right thing with the
	 * post parse analysis query tree inference clause representation.
	 */
}
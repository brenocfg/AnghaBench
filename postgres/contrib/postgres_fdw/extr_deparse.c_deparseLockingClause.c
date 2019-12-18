#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* scanrel; TYPE_4__* root; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ deparse_expr_cxt ;
struct TYPE_15__ {int /*<<< orphan*/  lower_subquery_rels; } ;
struct TYPE_14__ {int strength; } ;
struct TYPE_13__ {int /*<<< orphan*/  rowMarks; TYPE_1__* parse; } ;
struct TYPE_12__ {int /*<<< orphan*/  relids; scalar_t__ fdw_private; } ;
struct TYPE_10__ {int resultRelation; scalar_t__ commandType; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_3__ RelOptInfo ;
typedef  TYPE_4__ PlannerInfo ;
typedef  TYPE_5__ PlanRowMark ;
typedef  TYPE_6__ PgFdwRelationInfo ;

/* Variables and functions */
 scalar_t__ BMS_MULTIPLE ; 
 scalar_t__ CMD_DELETE ; 
 scalar_t__ CMD_UPDATE ; 
 scalar_t__ IS_JOIN_REL (TYPE_3__*) ; 
#define  LCS_FORKEYSHARE 132 
#define  LCS_FORNOKEYUPDATE 131 
#define  LCS_FORSHARE 130 
#define  LCS_FORUPDATE 129 
#define  LCS_NONE 128 
 int /*<<< orphan*/  REL_ALIAS_PREFIX ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bms_is_member (int,int /*<<< orphan*/ ) ; 
 scalar_t__ bms_membership (int /*<<< orphan*/ ) ; 
 int bms_next_member (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* get_plan_rowmark (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
deparseLockingClause(deparse_expr_cxt *context)
{
	StringInfo	buf = context->buf;
	PlannerInfo *root = context->root;
	RelOptInfo *rel = context->scanrel;
	PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) rel->fdw_private;
	int			relid = -1;

	while ((relid = bms_next_member(rel->relids, relid)) >= 0)
	{
		/*
		 * Ignore relation if it appears in a lower subquery.  Locking clause
		 * for such a relation is included in the subquery if necessary.
		 */
		if (bms_is_member(relid, fpinfo->lower_subquery_rels))
			continue;

		/*
		 * Add FOR UPDATE/SHARE if appropriate.  We apply locking during the
		 * initial row fetch, rather than later on as is done for local
		 * tables. The extra roundtrips involved in trying to duplicate the
		 * local semantics exactly don't seem worthwhile (see also comments
		 * for RowMarkType).
		 *
		 * Note: because we actually run the query as a cursor, this assumes
		 * that DECLARE CURSOR ... FOR UPDATE is supported, which it isn't
		 * before 8.3.
		 */
		if (relid == root->parse->resultRelation &&
			(root->parse->commandType == CMD_UPDATE ||
			 root->parse->commandType == CMD_DELETE))
		{
			/* Relation is UPDATE/DELETE target, so use FOR UPDATE */
			appendStringInfoString(buf, " FOR UPDATE");

			/* Add the relation alias if we are here for a join relation */
			if (IS_JOIN_REL(rel))
				appendStringInfo(buf, " OF %s%d", REL_ALIAS_PREFIX, relid);
		}
		else
		{
			PlanRowMark *rc = get_plan_rowmark(root->rowMarks, relid);

			if (rc)
			{
				/*
				 * Relation is specified as a FOR UPDATE/SHARE target, so
				 * handle that.  (But we could also see LCS_NONE, meaning this
				 * isn't a target relation after all.)
				 *
				 * For now, just ignore any [NO] KEY specification, since (a)
				 * it's not clear what that means for a remote table that we
				 * don't have complete information about, and (b) it wouldn't
				 * work anyway on older remote servers.  Likewise, we don't
				 * worry about NOWAIT.
				 */
				switch (rc->strength)
				{
					case LCS_NONE:
						/* No locking needed */
						break;
					case LCS_FORKEYSHARE:
					case LCS_FORSHARE:
						appendStringInfoString(buf, " FOR SHARE");
						break;
					case LCS_FORNOKEYUPDATE:
					case LCS_FORUPDATE:
						appendStringInfoString(buf, " FOR UPDATE");
						break;
				}

				/* Add the relation alias if we are here for a join relation */
				if (bms_membership(rel->relids) == BMS_MULTIPLE &&
					rc->strength != LCS_NONE)
					appendStringInfo(buf, " OF %s%d", REL_ALIAS_PREFIX, relid);
			}
		}
	}
}
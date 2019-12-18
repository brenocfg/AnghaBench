#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int indexcol; TYPE_2__* index; } ;
typedef  TYPE_1__ ec_member_matches_arg ;
struct TYPE_11__ {int /*<<< orphan*/  ec_collation; int /*<<< orphan*/  ec_opfamilies; } ;
struct TYPE_10__ {scalar_t__ em_expr; } ;
struct TYPE_9__ {int nkeycolumns; scalar_t__ relam; int /*<<< orphan*/ * indexcollations; int /*<<< orphan*/ * opfamily; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_2__ IndexOptInfo ;
typedef  TYPE_3__ EquivalenceMember ;
typedef  TYPE_4__ EquivalenceClass ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BTREE_AM_OID ; 
 int /*<<< orphan*/  IndexCollMatchesExprColl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_member_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int match_index_to_operand (int /*<<< orphan*/ *,int,TYPE_2__*) ; 

__attribute__((used)) static bool
ec_member_matches_indexcol(PlannerInfo *root, RelOptInfo *rel,
						   EquivalenceClass *ec, EquivalenceMember *em,
						   void *arg)
{
	IndexOptInfo *index = ((ec_member_matches_arg *) arg)->index;
	int			indexcol = ((ec_member_matches_arg *) arg)->indexcol;
	Oid			curFamily;
	Oid			curCollation;

	Assert(indexcol < index->nkeycolumns);

	curFamily = index->opfamily[indexcol];
	curCollation = index->indexcollations[indexcol];

	/*
	 * If it's a btree index, we can reject it if its opfamily isn't
	 * compatible with the EC, since no clause generated from the EC could be
	 * used with the index.  For non-btree indexes, we can't easily tell
	 * whether clauses generated from the EC could be used with the index, so
	 * don't check the opfamily.  This might mean we return "true" for a
	 * useless EC, so we have to recheck the results of
	 * generate_implied_equalities_for_column; see
	 * match_eclass_clauses_to_index.
	 */
	if (index->relam == BTREE_AM_OID &&
		!list_member_oid(ec->ec_opfamilies, curFamily))
		return false;

	/* We insist on collation match for all index types, though */
	if (!IndexCollMatchesExprColl(curCollation, ec->ec_collation))
		return false;

	return match_index_to_operand((Node *) em->em_expr, indexcol, index);
}
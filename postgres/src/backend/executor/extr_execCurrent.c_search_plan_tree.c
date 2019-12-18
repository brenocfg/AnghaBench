#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int as_nplans; TYPE_3__** appendplans; } ;
struct TYPE_12__ {int ms_nplans; TYPE_3__** mergeplans; } ;
struct TYPE_11__ {int /*<<< orphan*/ * chgParam; struct TYPE_11__* lefttree; } ;
struct TYPE_10__ {int /*<<< orphan*/  ss_currentRelation; } ;
struct TYPE_9__ {TYPE_3__* subplan; } ;
typedef  TYPE_1__ SubqueryScanState ;
typedef  TYPE_2__ ScanState ;
typedef  TYPE_3__ PlanState ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ MergeAppendState ;
typedef  TYPE_5__ AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
#define  T_AppendState 140 
#define  T_BitmapHeapScanState 139 
#define  T_CustomScanState 138 
#define  T_ForeignScanState 137 
#define  T_IndexOnlyScanState 136 
#define  T_IndexScanState 135 
#define  T_LimitState 134 
#define  T_MergeAppendState 133 
#define  T_ResultState 132 
#define  T_SampleScanState 131 
#define  T_SeqScanState 130 
#define  T_SubqueryScanState 129 
#define  T_TidScanState 128 
 int nodeTag (TYPE_3__*) ; 

__attribute__((used)) static ScanState *
search_plan_tree(PlanState *node, Oid table_oid,
				 bool *pending_rescan)
{
	ScanState  *result = NULL;

	if (node == NULL)
		return NULL;
	switch (nodeTag(node))
	{
			/*
			 * Relation scan nodes can all be treated alike
			 */
		case T_SeqScanState:
		case T_SampleScanState:
		case T_IndexScanState:
		case T_IndexOnlyScanState:
		case T_BitmapHeapScanState:
		case T_TidScanState:
		case T_ForeignScanState:
		case T_CustomScanState:
			{
				ScanState  *sstate = (ScanState *) node;

				if (RelationGetRelid(sstate->ss_currentRelation) == table_oid)
					result = sstate;
				break;
			}

			/*
			 * For Append, we must look through the members; watch out for
			 * multiple matches (possible if it was from UNION ALL)
			 */
		case T_AppendState:
			{
				AppendState *astate = (AppendState *) node;
				int			i;

				for (i = 0; i < astate->as_nplans; i++)
				{
					ScanState  *elem = search_plan_tree(astate->appendplans[i],
														table_oid,
														pending_rescan);

					if (!elem)
						continue;
					if (result)
						return NULL;	/* multiple matches */
					result = elem;
				}
				break;
			}

			/*
			 * Similarly for MergeAppend
			 */
		case T_MergeAppendState:
			{
				MergeAppendState *mstate = (MergeAppendState *) node;
				int			i;

				for (i = 0; i < mstate->ms_nplans; i++)
				{
					ScanState  *elem = search_plan_tree(mstate->mergeplans[i],
														table_oid,
														pending_rescan);

					if (!elem)
						continue;
					if (result)
						return NULL;	/* multiple matches */
					result = elem;
				}
				break;
			}

			/*
			 * Result and Limit can be descended through (these are safe
			 * because they always return their input's current row)
			 */
		case T_ResultState:
		case T_LimitState:
			result = search_plan_tree(node->lefttree,
									  table_oid,
									  pending_rescan);
			break;

			/*
			 * SubqueryScan too, but it keeps the child in a different place
			 */
		case T_SubqueryScanState:
			result = search_plan_tree(((SubqueryScanState *) node)->subplan,
									  table_oid,
									  pending_rescan);
			break;

		default:
			/* Otherwise, assume we can't descend through it */
			break;
	}

	/*
	 * If we found a candidate at or below this node, then this node's
	 * chgParam indicates a pending rescan that will affect the candidate.
	 */
	if (result && node->chgParam != NULL)
		*pending_rescan = true;

	return result;
}
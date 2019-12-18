#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent_relid; } ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  int /*<<< orphan*/  PlannerInfo ;
typedef  TYPE_1__ AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * adjust_child_relids (int /*<<< orphan*/ *,int,TYPE_1__**) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bms_overlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__** find_appinfos_by_relids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__**) ; 

Relids
adjust_child_relids_multilevel(PlannerInfo *root, Relids relids,
							   Relids child_relids, Relids top_parent_relids)
{
	AppendRelInfo **appinfos;
	int			nappinfos;
	Relids		parent_relids = NULL;
	Relids		result;
	Relids		tmp_result = NULL;
	int			cnt;

	/*
	 * If the given relids set doesn't contain any of the top parent relids,
	 * it will remain unchanged.
	 */
	if (!bms_overlap(relids, top_parent_relids))
		return relids;

	appinfos = find_appinfos_by_relids(root, child_relids, &nappinfos);

	/* Construct relids set for the immediate parent of the given child. */
	for (cnt = 0; cnt < nappinfos; cnt++)
	{
		AppendRelInfo *appinfo = appinfos[cnt];

		parent_relids = bms_add_member(parent_relids, appinfo->parent_relid);
	}

	/* Recurse if immediate parent is not the top parent. */
	if (!bms_equal(parent_relids, top_parent_relids))
	{
		tmp_result = adjust_child_relids_multilevel(root, relids,
													parent_relids,
													top_parent_relids);
		relids = tmp_result;
	}

	result = adjust_child_relids(relids, nappinfos, appinfos);

	/* Free memory consumed by any intermediate result. */
	if (tmp_result)
		bms_free(tmp_result);
	bms_free(parent_relids);
	pfree(appinfos);

	return result;
}
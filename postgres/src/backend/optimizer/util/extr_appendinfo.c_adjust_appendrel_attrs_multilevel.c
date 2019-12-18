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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Bitmapset ;
typedef  TYPE_1__ AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * adjust_appendrel_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_1__**) ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bms_num_members (int /*<<< orphan*/ *) ; 
 TYPE_1__** find_appinfos_by_relids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (TYPE_1__**) ; 

Node *
adjust_appendrel_attrs_multilevel(PlannerInfo *root, Node *node,
								  Relids child_relids,
								  Relids top_parent_relids)
{
	AppendRelInfo **appinfos;
	Bitmapset  *parent_relids = NULL;
	int			nappinfos;
	int			cnt;

	Assert(bms_num_members(child_relids) == bms_num_members(top_parent_relids));

	appinfos = find_appinfos_by_relids(root, child_relids, &nappinfos);

	/* Construct relids set for the immediate parent of given child. */
	for (cnt = 0; cnt < nappinfos; cnt++)
	{
		AppendRelInfo *appinfo = appinfos[cnt];

		parent_relids = bms_add_member(parent_relids, appinfo->parent_relid);
	}

	/* Recurse if immediate parent is not the top parent. */
	if (!bms_equal(parent_relids, top_parent_relids))
		node = adjust_appendrel_attrs_multilevel(root, node, parent_relids,
												 top_parent_relids);

	/* Now translate for this child */
	node = adjust_appendrel_attrs(root, node, nappinfos, appinfos);

	pfree(appinfos);

	return node;
}
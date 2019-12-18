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
struct TYPE_10__ {int /*<<< orphan*/  parent_relid; } ;
struct TYPE_9__ {size_t simple_rel_array_size; TYPE_3__** append_rel_array; } ;
struct TYPE_8__ {scalar_t__ reloptkind; size_t relid; } ;
typedef  int /*<<< orphan*/ * Relids ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ PlannerInfo ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_3__ AppendRelInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ RELOPT_BASEREL ; 
 scalar_t__ RELOPT_OTHER_MEMBER_REL ; 
 int /*<<< orphan*/ * bms_add_member (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_base_rel (TYPE_2__*,int /*<<< orphan*/ ) ; 

Relids
find_childrel_parents(PlannerInfo *root, RelOptInfo *rel)
{
	Relids		result = NULL;

	Assert(rel->reloptkind == RELOPT_OTHER_MEMBER_REL);
	Assert(rel->relid > 0 && rel->relid < root->simple_rel_array_size);

	do
	{
		AppendRelInfo *appinfo = root->append_rel_array[rel->relid];
		Index		prelid = appinfo->parent_relid;

		result = bms_add_member(result, prelid);

		/* traverse up to the parent rel, loop if it's also a child rel */
		rel = find_base_rel(root, prelid);
	} while (rel->reloptkind == RELOPT_OTHER_MEMBER_REL);

	Assert(rel->reloptkind == RELOPT_BASEREL);

	return result;
}
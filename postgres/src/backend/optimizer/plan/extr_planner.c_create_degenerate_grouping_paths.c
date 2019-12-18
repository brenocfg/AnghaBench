#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* parse; } ;
struct TYPE_13__ {scalar_t__ havingQual; int /*<<< orphan*/  groupingSets; } ;
struct TYPE_12__ {int /*<<< orphan*/  reltarget; } ;
typedef  TYPE_1__ RelOptInfo ;
typedef  TYPE_2__ Query ;
typedef  TYPE_3__ PlannerInfo ;
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  add_path (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ create_append_path (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ create_group_result_path (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_degenerate_grouping_paths(PlannerInfo *root, RelOptInfo *input_rel,
								 RelOptInfo *grouped_rel)
{
	Query	   *parse = root->parse;
	int			nrows;
	Path	   *path;

	nrows = list_length(parse->groupingSets);
	if (nrows > 1)
	{
		/*
		 * Doesn't seem worthwhile writing code to cons up a generate_series
		 * or a values scan to emit multiple rows. Instead just make N clones
		 * and append them.  (With a volatile HAVING clause, this means you
		 * might get between 0 and N output rows. Offhand I think that's
		 * desired.)
		 */
		List	   *paths = NIL;

		while (--nrows >= 0)
		{
			path = (Path *)
				create_group_result_path(root, grouped_rel,
										 grouped_rel->reltarget,
										 (List *) parse->havingQual);
			paths = lappend(paths, path);
		}
		path = (Path *)
			create_append_path(root,
							   grouped_rel,
							   paths,
							   NIL,
							   NIL,
							   NULL,
							   0,
							   false,
							   NIL,
							   -1);
	}
	else
	{
		/* No grouping sets, or just one, so one output row */
		path = (Path *)
			create_group_result_path(root, grouped_rel,
									 grouped_rel->reltarget,
									 (List *) parse->havingQual);
	}

	add_path(grouped_rel, path);
}
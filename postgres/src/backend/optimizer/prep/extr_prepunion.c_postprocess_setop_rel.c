#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  int /*<<< orphan*/  PlannerInfo ;

/* Variables and functions */
 int /*<<< orphan*/  UPPERREL_SETOP ; 
 int /*<<< orphan*/  create_upper_paths_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cheapest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
postprocess_setop_rel(PlannerInfo *root, RelOptInfo *rel)
{
	/*
	 * We don't currently worry about allowing FDWs to contribute paths to
	 * this relation, but give extensions a chance.
	 */
	if (create_upper_paths_hook)
		(*create_upper_paths_hook) (root, UPPERREL_SETOP,
									NULL, rel, NULL);

	/* Select cheapest path */
	set_cheapest(rel);
}